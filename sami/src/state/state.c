// Copyright 2023 edg

#include <stdlib.h>

#include "sami/src/state/state.h"

struct sami_state* sami_create_state() {
        struct sami_state* state = malloc(sizeof(struct sami_state));

        if (state == NULL)
                return state;

        state->counter = 0;
        state->counter2 = 1;
        return state;
}

i32 sami_destroy_state(struct sami_state* state) {
        if (state == NULL)
                return -1;

        free(state);
        return 0;
}

