// Copyright 2023 edg

#pragma once

#include "terminal/src/ui/state/state.h"
#include "terminal/src/ui/window/window.h"
#include "utils/types.h"

struct layout {
        struct window* main;
};

struct layout* create_layout(void);

i32 destroy_layout(struct layout* layout);

i32 update_layout_from_state(struct layout* layout, struct state* state);
