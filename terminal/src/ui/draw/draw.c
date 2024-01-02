// Copyright 2023 edg

#include "lib/ncurses/include/curses.h"

#include "terminal/src/ui/draw/draw.h"

i32 terminal_ui_draw(struct ui* ui) {
        if (ui->ui_state->needs_clearing) {
                clear();
                ui->ui_state->needs_clearing = false;
        }

        start_color();

        init_pair(1, COLOR_MAGENTA, 0);
        init_pair(2, COLOR_MAGENTA, 0);

        attron(COLOR_PAIR(1));
        attron(A_BOLD);

        move(10, 43);

        addstr("Hot reloadable ui\n");

        attroff(COLOR_PAIR(1));
        attroff(A_BOLD);

        move(0, 0);
        printw("counter: %d\n", ui->ui_state->counter);

        return 0;
}
