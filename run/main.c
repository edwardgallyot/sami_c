// Copyright 2023 edg

#include <stdio.h>

#include "sami/src/sami.h"
#include "portaudio/include/portaudio.h"

int main(void) {
        sami_engine* engine = sami_create_engine();
        Pa_Initialize();

        int v = Pa_GetVersion();

        printf("%d\n", v);

        // TODO(edg): Hot Reloading!

        if (sami_destroy_engine(engine) != 0) {
                return -1;
        }

        return 0;
}
