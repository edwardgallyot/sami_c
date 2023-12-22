// Copyright 2023 edg

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "src/hot_reload/hot_reload.h"

#define MAX_CHAR_BUFFER_SIZE (100)

static char file_path[MAX_CHAR_BUFFER_SIZE];
static char entry_point[MAX_CHAR_BUFFER_SIZE];
static char exit_point[MAX_CHAR_BUFFER_SIZE];

#define QUIT_FROM_TERMINAL (1)

static void* state;

static void* lib_handle;

typedef void* (shared_func)(void*);

static shared_func* reload_func;
static shared_func* quit_func;

i32 init_hot_reloader(void* s, const char* file, const char* entry, const char* exit) {
        memset(file_path, 0, sizeof(file_path));
        memset(entry_point, 0, sizeof(entry_point));
        memset(exit_point, 0, sizeof(exit_point));

        if (strnlen(file,  MAX_CHAR_BUFFER_SIZE) >= MAX_CHAR_BUFFER_SIZE)
                return -1;

        if (strnlen(entry,  MAX_CHAR_BUFFER_SIZE) >= MAX_CHAR_BUFFER_SIZE)
                return -1;

        if (strnlen(exit,  MAX_CHAR_BUFFER_SIZE) >= MAX_CHAR_BUFFER_SIZE)
                return -1;

        strncpy(file_path, file, MAX_CHAR_BUFFER_SIZE);
        strncpy(entry_point, entry, MAX_CHAR_BUFFER_SIZE);
        strncpy(exit_point, exit, MAX_CHAR_BUFFER_SIZE);

        state = s;
        return 0;
}

static i32 handle_hot_reload() {
        if (lib_handle)
                dlclose(lib_handle);

        lib_handle = dlopen(file_path, RTLD_NOW);

        if (!lib_handle)
                return -1;

        dlerror();
        *(void **) (&reload_func) = dlsym(lib_handle, entry_point);

        if (reload_func)
                state = reload_func(state);

        dlclose(lib_handle);
        lib_handle = NULL;
        return 0;
}

static char handle_stdin() {
        char input[256];

        memset(input, 0, sizeof(input));
        if (fgets(input, sizeof(input), stdin) == NULL) {
                return 0;
        }
        if (input[0] == 'q') {
                return 'q';
        }

        if (input[0] == 'l') {
                return 'q';
        }
        return 0;
}

static i32 handle_file_changes() {
        fd_set fds;

        i32 stdin_fd = fileno(stdin);


        FD_ZERO(&fds);
        FD_SET(stdin_fd, &fds);

        i32 err;
        err = select(1, &fds, NULL, NULL, NULL);

        if (err < 0)
                return err;

        if (FD_ISSET(stdin_fd, &fds)) {
                char in = handle_stdin();

                if (in == 'q')
                        return QUIT_FROM_TERMINAL;

                if (in == 'l')
                        return 0;
        }

        return 0;
}

static i32 handle_quit() {
        if (lib_handle)
                dlclose(lib_handle);

        lib_handle = dlopen(file_path, RTLD_NOW);

        if (!lib_handle)
                return -1;

        dlerror();
        *(void **) (&quit_func) = dlsym(lib_handle, exit_point);

        if (quit_func)
                state = quit_func(state);

        dlclose(lib_handle);
        lib_handle = NULL;
        return 0;
}

static i32 run_main_loop() {
        i32 err = 0;

        err = handle_hot_reload();

        if (err != 0)
                return err;

        err = handle_file_changes();

        if (err == QUIT_FROM_TERMINAL) {
                err = handle_quit();

                if (err < 0)
                        return -1;
                else
                        return QUIT_FROM_TERMINAL;
        }

        if (err != 0)
                return err;

        return 0;
}

i32 run_hot_reloader() {
        while (true) {
                i32 err = run_main_loop();

                if (err == 0)
                        continue;
                else if (err == QUIT_FROM_TERMINAL)
                        break;
                else
                        return err;
        }

        return 0;
}

