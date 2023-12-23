// Copyright 2023 edg

#pragma once

#include "src/state/state.h"
#include "utils/types.h"


typedef struct sami_engine {
        sami_state* state;
} sami_engine;

typedef struct sami_engine sami_engine;

sami_engine* sami_engine_create_engine();

i32 sami_engine_free_engine(sami_engine*);
