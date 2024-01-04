// Copyright 2023 edg

#pragma once

#include "utils/types.h"

struct state {
        // Init flag
        bool needs_clearing;

        // Destory flag
        bool should_quit;

        // Test state
        int counter;
};

struct state* create_state(void);

i32 destroy_state(struct state* state);

i32 state_process_input(struct state* state, char c);
