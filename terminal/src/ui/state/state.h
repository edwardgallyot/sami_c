// Copyright 2023 edg

#pragma once

#include "utils/types.h"

enum state_mode {
        state_mode_browse = 0,
        state_mode_input,
};

enum state_window {
        state_window_main = 0,
};

struct state {
        // Init flag
        bool needs_clearing;

        // Destory flag
        bool should_quit;

        // Test state
        i32 counter;

        // The current row and column of the state
        i32 height;
        i32 width;

        // The cursor position
        i32 cursor_position_y;
        i32 cursor_position_x;

        // Current mode of the state
        enum state_mode mode;

        // Current selected window
        enum state_window current_window;
};

struct state* create_state(void);

i32 destroy_state(struct state* state);

i32 state_process_input(struct state* state, char c);

i32 update_state(struct state* state);
