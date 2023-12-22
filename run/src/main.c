// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "portaudio/include/portaudio.h"
#include "src/hot_reload/hot_reload.h"

static const char* lib_path = "/home/edgallyot/dev/sami_c/build/sami/libsami.so";
static const char* load = "sami_engine_reload";
static const char* refresh = "sami_engine_refresh";
static const char* destroy = "sami_engine_quit";


int main(void) {
        Pa_Initialize();

        char* working_dir = getcwd(NULL, 100);

        printf("%s", working_dir);

        free(working_dir);

        void* e = NULL;

        if (init_hot_reloader(e, lib_path, load, refresh, destroy) != 0)
                return -1;

        i32 err = run_hot_reloader();

        if (err != 0) {
                printf("Error running hot reloader.");
        }

        return 0;
}
