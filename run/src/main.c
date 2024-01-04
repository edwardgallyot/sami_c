// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/portaudio/include/portaudio.h"
#include "hot_reload/src/hot_reload.h"
#include "utils/log.h"

#define num_files 6

const char* watch_list[num_files] = {
        "../sami/src/sami.c",
        "../sami/src/sami.h",
        "../sami/src/engine/engine.c",
        "../sami/src/engine/engine.h",
        "../sami/src/state/state.c",
        "../sami/src/state/state.h"
};

static const char* lib_path = "./sami/libsami.so";
static const char* build = "cmake .. && cmake --build .";
static const char* load = "sami_engine_reload";
static const char* destroy = "sami_engine_quit";

static void on_lib_reload(void) {
        printf("Lock!\n");
}

static void on_lib_reloaded(void) {
        printf("Unlock!\n");
}

int main(void) {
        Pa_Initialize();

        char* working_dir = getcwd(NULL, 100);

        printf("%s", working_dir);

        free(working_dir);

        struct hot_reloader reloader = {
                .file = lib_path,

                .load = load,
                .destroy = destroy,

                .build = build,

                .data = NULL,

                .on_reload = on_lib_reload,
                .on_reloaded = on_lib_reloaded,

                .watch_list = NULL,
        };

        for (i32 f = 0; f < num_files; ++f) {
                if (add_file_to_watch_list(&reloader, watch_list[f]) != 0)
                        return -1;
        }

        i32 err = run_hot_reloader(&reloader);


        if (err != 0)
                ERROR("Error running hot reloader.\n");

        clean_hot_reloader(&reloader);


        return 0;
}
