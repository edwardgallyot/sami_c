// Copyright 2023 edg

#pragma once

#include <sys/stat.h>
#include "utils/types.h"

typedef void(*on_reload_callback)(void);

typedef struct watch_list_item {
        const char* file_path;
        struct watch_list_item* next;
        struct stat last_stats;
} watch_list_item;

typedef struct hot_reloader {
        const char* file;

        // load and destroy functions
        const char* load;
        const char* destroy;

        const char* build;

        // state
        void* data;

        // callbacks
        on_reload_callback on_reload;
        on_reload_callback on_reloaded;

        // list of file descriptors
        watch_list_item* watch_list;
} hot_reloader;

i32 init_hot_reloader(hot_reloader* reloader);

i32 run_hot_reloader(hot_reloader* reloader);

i32 add_file_to_watch_list(hot_reloader* reloader, const char* file_path);

i32 clean_hot_reloader(hot_reloader* reloader);
