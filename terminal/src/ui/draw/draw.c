// Copyright 2024 edg

#include "lib/ncurses/include/curses.h"
#include "terminal/src/ui/colour/colour.h"

#include "terminal/src/ui/draw/draw.h"

i32 terminal_ui_draw(struct ui* ui) {
        if (ui->state->needs_clearing) {
                clear();
                ui->state->needs_clearing = false;
        }



        turn_colour_on(colour_id_purple_fg);
        attron(A_BOLD);

        move(9, 10);

        addstr("Hot reloadable ui\n");

        turn_colour_off(colour_id_purple_fg);

        attroff(A_BOLD);

        move(10, 0);

        turn_colour_on(colour_id_cyan_fg);

        printw("=== counter: %d ===\n", ui->state->counter);

        turn_colour_off(colour_id_cyan_fg);


        move(20, 20);

        printw("Total num rows: %d,Total num columns: %d", 
               ui->state->total_rows,
               ui->state->total_columns);

        move(20, 20);

        if (ui->state->should_quit) {
                addstr("Quit requested");
        }

        return 0;
}
