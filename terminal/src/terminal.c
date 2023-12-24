// Copyright 2023 edg

#include "terminal/src/terminal.h"
#include "terminal/src/ui/ui.h"

#include <stdio.h>

void* sami_terminal_reload(void* ui) {
        if (ui != NULL) {
                terminal_destroy_ui(ui);
        }
        printf("Hello sami Terminal\n");
        return ui;
}

void* sami_terminal_quit(void* ui) {
        return ui;
}
