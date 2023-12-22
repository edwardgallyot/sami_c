// Copyright 2023 edg

#include "src/state/state.h"

#include <stdlib.h>

typedef struct sami_state {
} sami_state;

sami_state* sami_create_state() {
        sami_state* state = (sami_state*)malloc(sizeof(sami_state));
        return state;
}

i32 sami_destroy_state(sami_state* state) {
        if (state == NULL) 
                return -1;

        free(state);
        return 0;
}
