// Copyright 2024 edg

#include <stdlib.h>

#include "lib/ncurses/include/curses.h"
#include "terminal/src/ui/state/state.h"
#include "utils/log.h"


struct state* create_state(void) {
        struct state* state = malloc(sizeof(struct state));

        if (state == NULL)
                return state;

        state->counter = 0;
        state->needs_clearing = true;
        state->should_quit = false;

        state->cursor_position_y = 0;
        state->cursor_position_x = 0;

        state->width = -1;
        state->height = -1;

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

static i32 handle_browse_mode_up(struct state* state) {
        if (state->cursor_position_y > 0) {
                state->cursor_position_y -= 1;
        }
        return 0;
}


static i32 handle_browse_mode_left(struct state* state) {
        if (state->cursor_position_x > 0) {
                state->cursor_position_x -= 1;
        }
        return 0;
}

static i32 handle_browse_mode_right(struct state* state) {
        if (state->cursor_position_x < (state->width - 1)) {
                state->cursor_position_x += 1;
        }
        return 0;
}

static i32 handle_browse_mode_down(struct state* state) {
        if (state->cursor_position_y < (state->height - 1)) {
                state->cursor_position_y += 1;
        }
        return 0;
}

static i32 handle_browse_mode_quit(struct state* state) {
        if (!state->should_quit) {
                state->should_quit = true;
        }
        return 0;
}

static i32 handle_browse_mode(struct state* state, char c) {
        i32 result = 0;
        if (c == 'k') {
                result = handle_browse_mode_up(state);
        }

        else if (c == 'j') {
                result = handle_browse_mode_down(state);
        }

        else if (c == 'l') {
                result = handle_browse_mode_right(state);
        }

        else if (c == 'h') {
                result = handle_browse_mode_left(state);
        }

        else if (c == 'q') {
                result = handle_browse_mode_quit(state);
        }

        else if (result != 0)  {
                ERROR("Can't handle browse mode action: %c, result: %d", c, result);
        }

        return result;
}

i32 update_state(struct state* state) {
        getmaxyx(stdscr, state->height, state->width);

        if (state->height == -1 || state->width == -1) {
                return -1;
        }

        return 0;
}

i32 state_process_input(struct state* state, char c) {
        i32 result = 0;

        switch(state->mode)
        {
        case state_mode_browse:
                result = handle_browse_mode(state, c);
                break;
        default:
                break;
        }
        return result;
}

