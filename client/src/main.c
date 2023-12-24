// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "hot_reload/hot_reload.h"
#include "utils/log.h"

#define num_files 2

const char* watch_list[num_files] = {
        "../terminal/src/terminal.c",
        "../terminal/src/terminal.h",
};

static const char* lib_path = "./terminal/libterminal.so";
static const char* build = "cmake .. && cmake --build .";
static const char* load = "sami_terminal_reload";
static const char* destroy = "sami_terminal_quit";

static void on_lib_reload() {
        printf("Lock!\n");
}

static void on_lib_reloaded() {
        printf("Unlock!\n");
}

int main(void) {
        char* working_dir = getcwd(NULL, 100);

        printf("%s", working_dir);

        free(working_dir);

        hot_reloader reloader = {
                .file = lib_path,

                .load = load,
                .destroy = destroy,

                .build = build,

                .data = NULL,

                .on_reload = on_lib_reload,
                .on_reloaded = on_lib_reloaded,

                .watch_list = NULL,
        };

        for (i32 f = 0; f < num_files; ++f) {
                if (add_file_to_watch_list(&reloader, watch_list[f]) != 0)
                        return -1;
        }

        i32 err = run_hot_reloader(&reloader);


        if (err != 0)
                ERROR("Error running hot reloader.\n");

        clean_hot_reloader(&reloader);


        return 0;
}

