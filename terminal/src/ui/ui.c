// Copyright 2023 edg
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "atomic/src/atomic.h"
#include "lib/ncurses/include/curses.h"

#include "terminal/src/ui/ui.h"
#include "thread/src/thread.h"
#include "utils/log.h"

static const char* thread_name = "Ui thread";

static void* ui_thread(void* p) {
        struct ui* ui = (struct ui*)p;
        bool hello = true;
        while(true) {
                if (hello) {
                        clear();
                        printw("Hello this is better\n");
                        printw("At least I think...\n");
                        printw("Cool beans\n");
                        hello = false;
                }
                refresh();

                

                if (!atomic_load_bool(&ui->run)) {
                        atomic_store_bool(&ui->run, true);
                        break;
                }
        }

        return NULL;
}

static i32 run_main_ui_loop(struct ui* ui) {
        atomic_store_bool(&ui->run, true);
        ui->ui_thread = create_thread(thread_name, ui_thread, ui);
        return 0;
}

struct ui* terminal_build_ui() {
        printf("Building\n");

        struct ui* new_ui = malloc(sizeof(struct ui));

        if (new_ui == NULL) {
                ERROR("Malloc failed.");
                return NULL;
        }

        new_ui->counter = 0;
        new_ui->run = false;
        new_ui->ui_thread = NULL;

        return new_ui;
}

i32 terminal_run_ui(struct ui* ui) {
        if (stdscr == NULL) {
                initscr();
        } else {
                endwin();
                initscr();
        }

        run_main_ui_loop(ui);

        return 0;
}

i32 terminal_destroy_ui(struct ui* ui) {
        if (ui == NULL) {
                ERROR("Ui pointer is null on destroy");
                return -1;
        }

        if (atomic_load_bool(&ui->run)) {
                atomic_store_bool(&ui->run, false);
                while (!atomic_load_bool(&ui->run)) {}
        }

        if (stdscr != NULL) {
                endwin();
        }

        join_thread(ui->ui_thread);

        free(ui);
        ui = NULL;

        return 0;
}
