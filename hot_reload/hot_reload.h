// Copyright 2023 edg

#pragma once

#include "utils/types.h"

typedef struct hot_reloader {
        const char* file;
        const char* load;
        const char* destroy;
        void* data;
} hot_reloader;

i32 run_hot_reloader(hot_reloader* reloader);
