// Copyright 2023 edg

#pragma once

#include "terminal/src/ui/state/state.h"
#include "terminal/src/ui/window/window.h"
#include "utils/types.h"

struct layout {
        struct window* main;
};

i32 update_layout_from_state(struct state* state);
