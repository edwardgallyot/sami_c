// Copyright 2023 edg

#include "terminal/src/ui/colour/colour.h"
#include "lib/ncurses/include/curses.h"

void turn_colour_on(enum colour_id colour) {
        attron(COLOR_PAIR((int)colour));
}

void turn_colour_off(enum colour_id colour) {
        attroff(COLOR_PAIR((int)colour));
}

i32 init_colours(void) {
        start_color();

        init_pair(colour_id_purple_fg, COLOR_MAGENTA, 0);
        init_pair(colour_id_cyan_fg, COLOR_CYAN, 0);

        return 0;
}
