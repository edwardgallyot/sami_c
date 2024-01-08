// Copyright 2024 edg

#include <stdlib.h>

#include "terminal/src/ui/window/window.h"
#include "curses.h"
#include "utils/log.h"

struct window* create_window(void) {
        struct window* win = malloc(sizeof(struct window));

        if (win == NULL) {
                ERROR("Couldn't allocate window");
                return NULL; 
        }

        win->win = NULL;

        win->width = 0;
        win->height = 0;
        win->x = 0;
        win->y = 0;

        return win;
}

static i32 reset_inner_window(struct window* win) {
        if (win->win == NULL) {
                return -1;
        }
        wborder(
                win->win,
                ' ',
                ' ',
                ' ',
                ' ',
                ' ',
                ' ',
                ' ',
                ' '
        );
        wrefresh(win->win);
        delwin(win->win);
        return 0;
}

i32 destroy_window(struct window* win) {
        if (win == NULL) {
                ERROR("Can't destroy window: it's NULL");
                return -1;
        }

        i32 err = 0;
        err = reset_inner_window(win);

        if (err != 0) {
                ERROR("Error resetting inner window: %d", err);
        }

        free(win);

        return 0;
}


i32 window_update_dimensions(
        struct window* win,
        i32 height,
        i32 width,
        i32 y,
        i32 x
) {
        if (win == NULL) {
                ERROR("Can't update dimensions, win is NULL");
                return -1;
        }
        win->x = x;
        win->y = y;
        win->height = height;
        win->width = width;
        return 0;
}

static bool has_window_dimensions_changed(struct window* win) {
        i32 current_width = -1;
        i32 current_height = -1;

        getmaxyx(win->win, current_height, current_width);

        if (current_height == -1 || current_width == -1) {
                ERROR("Unable to get current window dimensions: width: %d, height: %d", current_width, current_height);
                return false;
        }

        i32 current_x = -1;
        i32 current_y = -1;

        getyx(win->win, current_y, current_x);

        if (current_y == -1 || current_x == -1) {
                ERROR("Unable to get current window position: width: %d, height: %d", current_width, current_height);
                return false;
        }

        bool changed = 
                win->width != current_width ||
                win->height != current_height ||
                win->x != current_x ||
                win->y != current_y;

        return changed;
}

i32 refresh_window(struct window* win) {
        if (win == NULL) {
                ERROR("Window passed is null");
                return -1;
        }

        if (win->win == NULL) {
                win->win = newwin(win->height, win->width, win->y, win->x);
                return 0;
        } 

        if (has_window_dimensions_changed(win)) {
                reset_inner_window(win);
                win->win = newwin(win->height, win->width, win->y, win->x);
        }

        // Default box.
        box(win->win, 0, 0);

        wrefresh(win->win);

        return 0;
}
