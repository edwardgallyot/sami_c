// Copyright 2023 edg
#include <stdlib.h>
#include <threads.h>

#include "lib/ncurses/include/curses.h"

#include "terminal/src/ui/ui.h"
#include "utils/log.h"


static i32 run_main_ui_loop(ui* ui) {
        printw("Hi sami\n");
        refresh();
        return 0;
}

static i32 test_thread(void* ) {
        printf("Hello thread\n");
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

        thrd_t thread;

        if (thrd_create(&thread, test_thread, NULL) != thrd_success) {
                ERROR("Error creating thread");
                return -1;
        }

        thrd_join(thread, NULL);

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
