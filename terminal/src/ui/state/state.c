
// Copyright 2024 edg

#include <stdlib.h>

#include "terminal/src/ui/state/state.h"
#include "utils/log.h"

struct state* create_state() {
        struct state* state = malloc(sizeof(struct state));

        if (state == NULL)
                return state;

        state->counter = 0;
        state->needs_clearing = false;
        return state;
}

i32 destroy_state(struct state* state) {
        if (state == NULL) {
                ERROR("State already null");
                return -1;
        }
        free(state);
        return 0;
}
