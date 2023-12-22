// Copyright 2023 edg

#include <stdio.h>

#include "portaudio/include/portaudio.h"
#include "src/hot_reload/hot_reload.h"

static const char* lib_path = "/home/edgallyot/dev/sami_c/build/sami/libsami.so";

int main(void) {
        Pa_Initialize();

        void* e = NULL;

        if (init_hot_reloader(e, lib_path) != 0)
                return -1;

        run_hot_reloader();

        return 0;
}
