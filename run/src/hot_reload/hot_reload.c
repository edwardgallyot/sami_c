// Copyright 2023 edg

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "src/hot_reload/hot_reload.h"

#define MAX_FILE_PATH_SIZE (100)

static char filePathBuffer[MAX_FILE_PATH_SIZE];

static void* engine;

static void* reload_handle;

typedef void* (sami_engine_reload_func)(void*);

static sami_engine_reload_func* func;

i32 init_hot_reloader(void* e, const char* path_to_dll) {
        memset(filePathBuffer, 0, sizeof(filePathBuffer));

        if (strnlen(path_to_dll,  MAX_FILE_PATH_SIZE) >= MAX_FILE_PATH_SIZE) {
                return -1;
        }

        strncpy(filePathBuffer, path_to_dll, MAX_FILE_PATH_SIZE);

        engine = e;
        return 0;
}

static i32 handle_hot_reload() {
        if (reload_handle) {
                dlclose(reload_handle);
        }

        reload_handle = dlopen(filePathBuffer, RTLD_NOW);

        if (!reload_handle) {
                printf("No reload handle");
                return -1;
        }

        dlerror();
        *(void **) (&func) = dlsym(reload_handle, "sami_engine_reload");

        if (func) {
                printf("Reloading\n");
                func(engine);
        }

        dlclose(reload_handle);
        reload_handle = NULL;
        return 0;
}

i32 run_hot_reloader() {
        while (true) {
                i32 err;

                err = handle_hot_reload();

                if (err != 0) {
                        return err;
                }

                sleep(1);
        }

        return 0;
}

