// Copyright 2023 edg

#pragma once

#include "utils/types.h"

i32 init_hot_reloader(
        void* e,
        const char* path_to_dll,
        const char* entry_point,
        const char* exit_point
);

i32 run_hot_reloader();
