// Copyright 2024 edg

#include "lib/ncurses/include/curses.h"
#include "terminal/src/ui/attribute/attribute.h"

void turn_on_bold(void) {
        attron(A_BOLD);
}

void turn_off_bold(void) {
        attroff(A_BOLD);
}
