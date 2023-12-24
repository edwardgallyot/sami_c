// Copyright 2023 edg

#pragma once

#include "src/state/state.h"
#include "utils/types.h"

typedef void (*process_function)(f32**, u32, u32);

typedef struct sami_engine {
        sami_state* state;
        process_function on_audio_callback;
} sami_engine;

typedef struct sami_engine sami_engine;

sami_engine* sami_engine_create_engine();

i32 sami_engine_free_engine(sami_engine*);
