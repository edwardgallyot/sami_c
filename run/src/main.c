// Copyright 2023 edg

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "sami/src/engine/engine.h"
#include "lib/portaudio/include/portaudio.h"
#include "hot_reload/src/hot_reload.h"
#include "utils/log.h"

#define SAMPLE_RATE (48000.0)

static i32 in_device_index = 0;
static i32 out_device_index = 0;

const char* watch_list[] = {
        "../sami/src/sami.c",
        "../sami/src/sami.h",
        "../sami/src/engine/engine.c",
        "../sami/src/engine/engine.h",
        "../sami/src/state/state.c",
        "../sami/src/state/state.h"
};

const i32 num_files = sizeof(watch_list) / sizeof(const char*);

static const char* lib_path = "./sami/libsami.so";
static const char* build = "cmake .. && cmake --build .";
static const char* load = "sami_engine_reload";
static const char* destroy = "sami_engine_quit";

static process_function sami_callback;
static const char* process_function_name = "sami_engine_process_audio";


static int test_callback( const void* input_buffer,
        void* output_buffer,
        u64 frames_per_buffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData 
) {
        return sami_callback(
                userData,
                input_buffer,
                output_buffer,
                frames_per_buffer,
                2
        );
}

static PaStream* stream;
static PaError err;

static i32 setup_pa_stream(void* data, i32 in_index, i32 out_index) {
        const PaDeviceInfo* in_device_info = Pa_GetDeviceInfo(in_index);
        const PaDeviceInfo* out_device_info = Pa_GetDeviceInfo(out_index);

        PaStreamParameters input_params;
        PaStreamParameters output_params;


        input_params.device = in_index;
        input_params.channelCount = 2;
        input_params.sampleFormat = paFloat32;
        input_params.suggestedLatency = in_device_info->defaultLowInputLatency;
        input_params.hostApiSpecificStreamInfo = NULL;

        output_params.device = out_index;
        output_params.channelCount = 2;
        output_params.sampleFormat = paFloat32;
        output_params.suggestedLatency = out_device_info->defaultLowOutputLatency;
        output_params.hostApiSpecificStreamInfo = NULL;
                

        err = Pa_OpenStream(
                &stream,
                &input_params,
                &output_params,
                SAMPLE_RATE,
                256,
                0,
                test_callback,
                data
        );

        if (err != paNoError) {
                ERROR("Couldn't open stream: %d: %s\n", err, Pa_GetErrorText(err));
                return -1;
        }

        err = Pa_StartStream(stream);
        if (err != paNoError) {
                ERROR("Can't start stream: %d: %s\n", err, Pa_GetErrorText(err));
                return -1;
        }

        return 0;
}

static i32 takedown_pa_stream(void) {
        err = Pa_StopStream(stream);
        if (err != paNoError) {
                ERROR("Can't stop stream: %d\n", err);
                return -1;
        }

        err = Pa_CloseStream(stream);
        if (err != paNoError) {
                ERROR("Can't close stream: %d\n", err);
                return -1;
        }

        return 0;
}

static i32 terminate_pa(void) {
        err = Pa_Terminate();
        if (err != paNoError) {
                ERROR("Couldn't initialising port audio: %d\n", err);
                return -1;
        }
        return 0;
}

static void on_lib_reload(void* data) {
        if (data != NULL) {
                ERROR("Unused data at :%p", data);
        }

        i32 err = takedown_pa_stream();
        if (err != 0) {
                ERROR("Error taking down pa stream");
        }
}

static void on_lib_reloaded(void* data) {
        if (data == NULL) {
                return;
        }
        struct hot_reloader* reloader = data;

        *(void **) (&sami_callback) = dlsym(reloader->lib_handle, process_function_name);
        if (sami_callback == NULL) {
                ERROR("sami_callback not loaded");
                return;
        }

        i32 err = setup_pa_stream(reloader->data, in_device_index, out_device_index);
        if (err != 0) {
                ERROR("Error setting up default pa stream: %d", err);
                return;
        }
}

static void sigint_handle(int sig) {
        if (sig != SIGINT) {
                return;
        }
        takedown_pa_stream();
        terminate_pa();
        printf("Interrupted. Exiting...\n");
        exit(0);
}

static void print_devices(void) {
        i32 i;
        i32 end = Pa_GetDeviceCount();
        for (i = 0; i != end; ++i) {
                PaDeviceInfo const* info = Pa_GetDeviceInfo(i);
                if (!info) {
                        continue;
                }
                printf("%d: %s\n", i, info->name);
        }
}

static bool is_device_valid(i32 index) {
        i32 i;
        i32 end = Pa_GetDeviceCount();
        for (i = 0; i != end; ++i) {
                PaDeviceInfo const* info = Pa_GetDeviceInfo(i);
                if (!info) {
                        continue;
                }
                if (i == index) {
                        return true;
                }
        }
        return false;
}

static i32 get_device_selection(const char* prompt) {
        char buf[10];
        i32 dev = -1;
        bool valid = false;

        print_devices();
        while (!valid) {
                printf("\n%s",  prompt);
                if (!fgets(buf, sizeof(buf), stdin)) {
                        continue;
                }

                if (sscanf(buf, "%d", &dev) != 1) {
                        continue;
                }

                if(is_device_valid(dev)) {
                        valid = true;
                }
        }
        if (valid) {
                return dev;;
        }
        return -1;
}

int main(void) {
        signal(SIGINT, sigint_handle);
        err = Pa_Initialize();
        if (err != paNoError) {
                ERROR("Couldn't initialising port audio: %d\n", err);
                return -1;
        }



        struct hot_reloader reloader = {
                .file = lib_path,

                .load = load,
                .destroy = destroy,

                .build = build,

                .data = NULL,
                .lib_handle = NULL,

                .on_reload = on_lib_reload,
                .on_reloaded = on_lib_reloaded,

                .watch_list = NULL,
        };

        for (i32 f = 0; f < num_files; ++f) {
                if (add_file_to_watch_list(&reloader, watch_list[f]) != 0) {
                        return -1;
                }
        }

        
        i32 err;

        in_device_index = get_device_selection("Gimme an input: ");

        if (in_device_index < 0) {
                ERROR("Error initialising device: %d", in_device_index);
                return in_device_index;
        }

        printf("Input %d selected.\n", in_device_index);

        out_device_index = get_device_selection("Gimme an output: ");

        if (out_device_index < 0) {
                ERROR("Error initialising device: %d", out_device_index);
                return out_device_index;
        }

        printf("Output %d selected.\n", out_device_index);


        err = init_hot_reloader(&reloader);

        if (err != 0) {
                ERROR("Error initialising hot_reloader: %d", err);
                return err;
        }

        printf("Running reloader\n");

        err = run_hot_reloader(&reloader);

        if (err != 0) {
                ERROR("Error running hot reloader.\n");
                return err;
        }

        err = takedown_pa_stream();

        if (err != 0) {
                ERROR("Error taking down audio stream.\n");
                return err;
        }

        err = clean_hot_reloader(&reloader);

        if (err != 0) {
                ERROR("Error cleaning up after hot reloader.\n");
                return err;
        }

        PaError pa_err =  Pa_Terminate();

        if (pa_err != paNoError) {
                ERROR("Error terminating pa.\n");
                return err;
        }

        return 0;
}
