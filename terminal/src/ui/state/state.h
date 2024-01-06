// Copyright 2023 edg

#pragma once

#include "utils/types.h"

enum state_mode {
        state_mode_browse,
};

struct state {
        // Init flag
        bool needs_clearing;

        // Destory flag
        bool should_quit;

        // Test state
        i32 counter;

        // The current row and column of the state
        i32 row;
        i32 column;

        // Current mode of the state
        enum state_mode mode;
};

struct state* create_state(void);

i32 destroy_state(struct state* state);

i32 state_process_input(struct state* state, char c);
