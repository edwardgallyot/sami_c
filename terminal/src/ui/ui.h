// Copyright 2023 edg

#pragma once

#include "thread/src/thread.h"
#include "utils/types.h"
#include "atomic/src/atomic.h"

struct ui {
        int counter;
        struct thread* ui_thread;
        atomic_bool run;
};

struct ui* terminal_build_ui();

i32 terminal_run_ui(struct ui* ui);

i32 terminal_destroy_ui(struct ui* ui);

