// Copyright 2023 edg

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "src/hot_reload/hot_reload.h"
#include "utils/log.h"

#define MAX_CHAR_BUFFER_SIZE (100)

typedef enum {
        hot_reload_err = -1,
        hot_reload_nothing = 0,
        hot_reload_quit = 1,
        hot_reload_reload = 2,
} hot_reload_action;

static void* state;

static void* lib_handle;

typedef void* (shared_func)(void*);

shared_func* func;

static i32 handle_lib_function(hot_reloader* hot_reloader, const char* name) {
        i32 err = 0;

        if (lib_handle)
                dlclose(lib_handle);

        lib_handle = dlopen(hot_reloader->file, RTLD_NOW);

        if (!lib_handle) {
                ERROR("No lib handle at: %p", lib_handle);
                return -1;
        }


        dlerror();
        *(void **) (&func)  = dlsym(lib_handle, name);

        if (func) {
                state = func(state);
        } else {
                ERROR("No function loaded from: %p", func);
                err = -1;
        }

        dlclose(lib_handle);
        lib_handle = NULL;

        return err;
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
                return 'l';
        }

        return 0;
}

static hot_reload_action handle_file_changes() {
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
                        return hot_reload_quit;

                if (in == 'l')
                        return hot_reload_reload;
        }

        return hot_reload_nothing;
}

static hot_reload_action run_main_loop(hot_reloader* hot_reloader) {
        i32 err = 0;

        if (err != 0)
                return err;

        hot_reload_action action = handle_file_changes();

        switch (action) {
        case hot_reload_quit:
                err = handle_lib_function(hot_reloader, hot_reloader->destroy);

                if (err == 0) {
                        return hot_reload_quit;
                } else {
                        ERROR("Error handling destory_func: %d", err);
                        return hot_reload_err;
                }
        case hot_reload_reload:
                err = handle_lib_function(hot_reloader, hot_reloader->load);

                if (err == 0) {
                        return hot_reload_nothing;
                } else {
                        ERROR("Error handling load_func: %d", err);
                        return hot_reload_err;
                }
        default:
                return hot_reload_nothing;
        }
}

i32 run_hot_reloader(hot_reloader* hot_reloader) {
        while (true) {
                hot_reload_action action = run_main_loop(hot_reloader);

                if (action == hot_reload_quit)
                        break;
                else if (action == hot_reload_err)
                        return -1;
                else
                        continue;
        }

        return 0;
}

