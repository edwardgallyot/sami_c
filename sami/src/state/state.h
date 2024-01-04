// Copyright 2023 edg

#pragma once

#include "utils/types.h"

struct sami_state {
        i32 counter;
        i32 counter2;
};

struct sami_state* sami_create_state();

i32 sami_destroy_state(struct sami_state* state);

i32 sami_state_process_input(struct sami_state* state, char c);
