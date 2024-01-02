// Copyright 2023 edg

#pragma once

#include "utils/types.h"

struct state {
        bool needs_clearing;
        int counter;
};

struct state* create_state();

i32 destroy_state(struct state* state);
