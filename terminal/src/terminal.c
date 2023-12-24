#include "terminal/src/terminal.h"

#include <stdio.h>
#include <lib/ncurses/include/curses.h>

void say_hello() {
        initscr();
        printf("Hello world\n");
}


void* sami_terminal_reload(void* reload) {
        printf("Hello sami Terminal\n");
        return reload;
}

void* sami_terminal_quit(void* engine) {
        return engine;
}
