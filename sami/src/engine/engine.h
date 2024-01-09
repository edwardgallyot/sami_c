// Copyright 2023 edg

#pragma once

#include "sami/src/state/state.h"
#include "utils/types.h"


struct sami_engine {
        struct sami_state* state;
};

typedef i32 (*process_function)(
        struct sami_engine*,
        const f32* ,
        f32*,
        u32,
        u32
);

struct sami_engine* sami_engine_create_engine(void);

i32 sami_engine_free_engine(struct sami_engine*);

i32 sami_engine_process_audio(
        struct sami_engine* engine,
        const f32* in,
        f32* out,
        u32 frames,
        u32 channels
);
