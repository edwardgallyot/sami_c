// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "portaudio/include/portaudio.h"
#include "src/hot_reload/hot_reload.h"

static const char* lib_path = "./sami/libsami.so";
static const char* entry_point = "sami_engine_reload";
static const char* exit_point = "sami_engine_quite";


int main(void) {
        Pa_Initialize();

        char* working_dir = getcwd(NULL, 100);

        printf("%s", working_dir);

        free(working_dir);

        void* e = NULL;

        if (init_hot_reloader(e, lib_path, entry_point, exit_point) != 0)
                return -1;

        run_hot_reloader();

        return 0;
}
