// Copyright 2023 edg

#include <stdio.h>

#include "sami/src/sami.h"
#include "portaudio/include/portaudio.h"

int main(void) {
        Pa_Initialize();

        int v = Pa_GetVersion();

        printf("%d\n", v);
        sami_init(true);
        return 0;
}
