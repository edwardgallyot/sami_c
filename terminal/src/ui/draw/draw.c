// Copyright 2024 edg

#include "lib/ncurses/include/curses.h"
#include "terminal/src/ui/attribute/attribute.h"
#include "terminal/src/ui/colour/colour.h"

#include "terminal/src/ui/draw/draw.h"
#include "utils/log.h"

i32 terminal_ui_draw(struct ui* ui) {
        if (ui->state->needs_clearing) {
                clear();
                ui->state->needs_clearing = false;
        }



        turn_colour_on(colour_id_purple_fg);
        turn_on_bold();

        move(9, 10);

        addstr("Hot reloadable ui\n");

        turn_off_bold();
        turn_colour_off(colour_id_purple_fg);

        move(10, 0);

        turn_colour_on(colour_id_cyan_fg);

        printw("=== counter: %d ===\n", ui->state->counter);

        turn_colour_off(colour_id_cyan_fg);


        move(20, 20);

        printw("Height: %d. Width: %d.", 
               ui->state->height,
               ui->state->width);

        move(ui->state->cursor_position_y, ui->state->cursor_position_x);

        if (ui->state->should_quit) {
                addstr("Quit requested");
        }

        return 0;
}

