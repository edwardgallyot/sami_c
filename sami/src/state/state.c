// Copyright 2023 edg

#include <stdlib.h>

#include "src/state/state.h"

sami_state* sami_create_state() {
        sami_state* state = (sami_state*)malloc(sizeof(sami_state));

        if (state == NULL)
                return state;

        state->counter = 0;
        state->counter2 = 1;
        return state;
}

i32 sami_destroy_state(sami_state* state) {
        if (state == NULL) 
                return -1;

        free(state);
        return 0;
}
