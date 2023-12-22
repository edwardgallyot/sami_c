// Copyright 2023 edg

#pragma once

#include "utils/types.h"

typedef struct sami_state {
        i32 counter;
        i32 counter2;
} sami_state;

sami_state* sami_create_state();

i32 sami_destroy_state(sami_state* state);
