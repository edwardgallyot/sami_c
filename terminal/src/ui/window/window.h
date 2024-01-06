#pragma once

#include "lib/ncurses/include/curses.h"
#include "utils/types.h"


struct window {
        WINDOW* win;

        // Dimensions
        i32 width;
        i32 height;
        i32 x;
        i32 y;
};

struct window* create_window(void);

i32 destroy_window(struct window* win);

i32 window_update_dimensions(
        struct window* win,
        i32 height,
        i32 width,
        i32 x,
        i32 y
);

i32 refresh_window(struct window* win);
