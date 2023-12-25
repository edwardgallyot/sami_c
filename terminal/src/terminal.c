// Copyright 2023 edg

#include "terminal/src/terminal.h"
#include "terminal/src/ui/ui.h"

#include <stdio.h>

void* sami_terminal_reload(void* ui) {
        if (ui != NULL) {
                terminal_destroy_ui(ui);
        }
        ui = terminal_build_ui();
        terminal_run_ui(ui);
        return ui;
}

void* sami_terminal_quit(void* ui) {
        terminal_destroy_ui(ui);
        return ui;
}
