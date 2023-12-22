// Copyright 2023 edg

#pragma once

#include "utils/types.h"

i32 init_hot_reloader(
        void* s,
        const char* file,
        const char* load,
        const char* refresh,
        const char* destroy
);

i32 run_hot_reloader();
