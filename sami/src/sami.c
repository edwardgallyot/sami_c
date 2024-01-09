// Copyright 2023 edg

#include "sami/src/sami.h"
#include <stdio.h>

struct sami_engine* sami_create_engine(void) {
        return sami_engine_create_engine();
}

i32 sami_destroy_engine(struct sami_engine* engine) {
        return sami_engine_free_engine(engine);
}

void* sami_engine_reload(void* engine) {
        if (engine != NULL) {
                sami_destroy_engine(engine);
        }

        struct sami_engine* eng = sami_create_engine();
        return eng;
}

void* sami_engine_quit(void* engine) {
        sami_destroy_engine(engine);
        return NULL;
}
