// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>

#include "hot_reload/src/hot_reload.h"
#include "utils/log.h"
#include "utils/types.h"

const char* watch_list[] = {
        "../terminal/src/terminal.c",
        "../terminal/src/terminal.h",
        "../terminal/src/ui/ui.c",
        "../terminal/src/ui/ui.h",
        "../terminal/src/ui/state/state.c",
        "../terminal/src/ui/state/state.h",
        "../terminal/src/ui/draw/draw.c",
        "../terminal/src/ui/draw/draw.h",
        "../terminal/src/ui/colour/colour.c",
        "../terminal/src/ui/colour/colour.h",
        "../terminal/src/ui/attribute/attribute.h",
        "../terminal/src/ui/attribute/attribute.c",
        "../terminal/src/ui/window/window.h",
        "../terminal/src/ui/window/window.c",
        "../terminal/CMakeLists.txt",
};

const i32 num_files = sizeof(watch_list) / sizeof(char*);

static const char* lib_path = "./terminal/libterminal.so";
static const char* build = "cmake .. && cmake --build .";
static const char* load = "sami_terminal_reload";
static const char* destroy = "sami_terminal_quit";

int main(void) {
        struct hot_reloader reloader = {
                .file = lib_path,

                .load = load,
                .destroy = destroy,

                .build = build,

                .data = NULL,

                .on_reload = NULL,
                .on_reloaded = NULL,

                .watch_list = NULL,
        };

        for (i32 f = 0; f < num_files; ++f) {
                if (add_file_to_watch_list(&reloader, watch_list[f]) != 0) {
                        return -1;
                }
        }

        i32 err;

        err = init_hot_reloader(&reloader);

        if (err != 0) {
                ERROR("Error initialising hot reloader.\n");
                return err;
        }

        err = run_hot_reloader(&reloader);

        if (err != 0) {
                ERROR("Error running hot reloader.\n");
                return err;
        }

        clean_hot_reloader(&reloader);

        printf("Exiting client...\n");


        return 0;
}

