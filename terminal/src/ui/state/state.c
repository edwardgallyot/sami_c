// Copyright 2024 edg

#include <stdlib.h>

#include "terminal/src/ui/state/state.h"
#include "utils/log.h"

struct state* create_state(void) {
        struct state* state = malloc(sizeof(struct state));

        if (state == NULL)
                return state;

        state->counter = 0;
        state->needs_clearing = true;
        state->should_quit = false;
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

static i32 state_handle_action_up(struct state* state) {
        state->counter++;
        return 0;
}


static i32 state_handle_action_left(struct state* state) {
        state->counter *= 2;
        return 0;
}

static i32 state_handle_action_right(struct state* state) {
        state->counter /= 2;
        return 0;
}

static i32 state_handle_action_down(struct state* state) {
        state->counter--;
        return 0;
}

static i32 state_handle_action_quit(struct state* state) {
        if (!state->should_quit) {
                state->should_quit = true;
        }
        return 0;
}

i32 state_process_input(struct state* state, char c) {
        i32 result = 0;

        if (c == 'k')
                result = state_handle_action_up(state);

        else if (c == 'j')
                result = state_handle_action_down(state);

        else if (c == 'l')
                result = state_handle_action_right(state);

        else if (c == 'h')
                result = state_handle_action_left(state);

        else if (c == 'q')
                result = state_handle_action_quit(state);


        else if (result != 0) 
                ERROR("Can't handle action: %c, result: %d", c, result);

        return result;
}

