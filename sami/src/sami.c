// Copyright 2023 edg

#include "src/sami.h"
#include <stdio.h>

i32 sami_init() {
        printf("Init sami!\n");
        return 0;
}

sami_engine* sami_create_engine() {
        return sami_engine_create_engine();
}

i32 sami_destroy_engine(sami_engine* engine) {
        return sami_engine_free_engine(engine);
}

void* sami_engine_reload(void* engine) {
        if (engine != NULL)
                sami_destroy_engine(engine);

        sami_engine* eng = sami_create_engine();

        printf("Reload!\n");
        printf("%d\n", eng->state->counter2);
        printf("%d\n", eng->state->counter);

        eng->state->counter++;
        eng->state->counter2--;

        return eng;
}

void* sami_engine_refresh(void* engine) {
        if (engine == NULL)
                engine = sami_create_engine();

        sami_engine* eng = (sami_engine*)engine;

        printf("Refresh!\n");
        printf("%d\n", eng->state->counter2);
        printf("%d\n", eng->state->counter);

        eng->state->counter++;
        eng->state->counter2--;

        return eng;
}

void* sami_engine_quit(void* engine) {
        sami_destroy_engine(engine);
        return NULL;
}
