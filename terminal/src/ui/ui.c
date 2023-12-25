// Copyright 2023 edg
#include <stdlib.h>

#include "lib/ncurses/include/curses.h"
#include "lib/tinycthread/source/tinycthread.h"

#include "terminal/src/ui/ui.h"
#include "utils/log.h"


static i32 run_main_ui_loop(ui* ui) {
        printw("Hi sami\n");
        refresh();
        return 0;
}

ui* terminal_build_ui() {
        ui* new_ui = malloc(sizeof(ui));

        if (new_ui == NULL) {
                ERROR("Malloc failed.");
        }

        return new_ui;
}

i32 terminal_run_ui(ui* ui) {
        if (stdscr == NULL) {
                initscr();
        } else {
                endwin();
                initscr();
        }

        run_main_ui_loop(ui);

        return 0;
}

i32 terminal_destroy_ui(ui* ui) {
        if (stdscr != NULL) {
                endwin();
        }

        if (ui == NULL) {
                ERROR("Ui pointer is null on destroy");
        }

        free(ui);

        return 0;
}
