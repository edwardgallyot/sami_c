// Copyright 2023 edg
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "atomic/src/atomic.h"
#include "lib/ncurses/include/curses.h"

#include "terminal/src/ui/ui.h"
#include "terminal/src/ui/colour/colour.h"
#include "terminal/src/ui/draw/draw.h"
#include "terminal/src/ui/state/state.h"
#include "thread/src/thread.h"
#include "utils/log.h"
#include "utils/time.h"

static const char* thread_name = "Ui thread";

static const i32 sleep_time_ui = 50000000;

static void terminal_cancel_ui_thread(struct ui* ui) {
        if (atomic_load_bool(&ui->run)) {
                atomic_store_bool(&ui->run, false);
                while (!atomic_load_bool(&ui->run)) {}
        }
}

static bool terminal_ui_cancelled(struct ui* ui) {
        if (!atomic_load_bool(&ui->run)) {
                atomic_store_bool(&ui->run, true);
                return true;
        }
        return false;
}

static char handle_std_in_no_block(void) {
        nodelay(stdscr, TRUE);
        int ch = getch();

        if (ch != ERR) {
                return (char)(ch);
        }

        return '\0';
}

static void* ui_thread(void* p) {
        struct ui* ui = (struct ui*)p;

        i32 err = init_colours();
        if (err != 0) {
                ERROR("Error initialising colours: %d", err);
        }

        while (true) {
                sleep_ns(sleep_time_ui);

                char c = handle_std_in_no_block();

                err = update_state(ui->state);

                err = state_process_input(ui->state, c);

                if (err != 0) {
                        ERROR("Error updating state: %d", err);
                }

                err = terminal_ui_draw(ui);

                if (err != 0) {
                        ERROR("Error drawing ui: %d", err);
                }
                

                if (terminal_ui_cancelled(ui)) {
                        break;
                }

                if (ui->state->should_quit) {
                        atomic_store_bool(&ui->run, false);
                        break;
                }
        }
        endwin();
        return NULL;
}

static i32 run_main_ui_loop(struct ui* ui) {
        atomic_store_bool(&ui->run, true);
        ui->thread = create_thread(thread_name, ui_thread, ui);
        return 0;
}

struct ui* terminal_build_ui(void) {
        printf("Building\n");

        struct ui* new_ui = malloc(sizeof(struct ui));

        if (new_ui == NULL) {
                ERROR("Malloc failed.");
                return NULL;
        }

        new_ui->run = false;
        new_ui->thread = NULL;
        new_ui->state = create_state();

        return new_ui;
}

static void terminal_setup_ui(void) {
        initscr();
        raw();
        cbreak();
        noecho();
}

i32 terminal_run_ui(struct ui* ui) {
        if (stdscr == NULL) {
                terminal_setup_ui();
        } else {
                endwin();
                terminal_setup_ui();
        }

        run_main_ui_loop(ui);

        return 0;
}

i32 terminal_destroy_ui(struct ui* ui) {
        if (ui == NULL) {
                ERROR("Ui pointer is null on destroy");
                return -1;
        }

        terminal_cancel_ui_thread(ui);

        if (stdscr != NULL) {
                endwin();
        }

        join_thread(ui->thread);
        destroy_state(ui->state);

        free(ui);
        ui = NULL;

        return 0;
}
