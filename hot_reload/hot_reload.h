// Copyright 2023 edg

#pragma once

#include "utils/types.h"

typedef void(*on_reload_callback)(void);

typedef struct hot_reloader {
        const char* file;
        const char* load;
        const char* destroy;
        void* data;
        on_reload_callback on_reload;
        on_reload_callback on_reloaded;
} hot_reloader;

i32 run_hot_reloader(hot_reloader* reloader);
