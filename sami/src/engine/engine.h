// Copyright 2023 edg

#pragma once

#include "src/state/state.h"
#include "utils/types.h"

typedef void (*process_function)(f32**, u32, u32);

struct sami_engine {
        struct sami_state* state;
        process_function on_audio_callback;
};

struct sami_engine* sami_engine_create_engine();

i32 sami_engine_free_engine(struct sami_engine*);
