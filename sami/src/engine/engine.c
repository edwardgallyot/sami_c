// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sami/src/engine/engine.h"
#include "utils/log.h"

struct sami_engine* sami_engine_create_engine(void) {
        struct sami_engine* engine = malloc(sizeof(struct sami_engine));

        if (engine == NULL) {
                return engine;
        }

        engine->state = sami_create_state();

        srand(time(NULL));

        return engine;
}

i32 sami_engine_free_engine(struct sami_engine* engine) {
        if (engine == NULL) {
                ERROR("Engine is NULL");
                return -1;
        }

        i32 err;

        err = sami_destroy_state(engine->state);

        if (err != 0) {
                ERROR("Error destroying state");
                return err;
        }

        free(engine);

        return 0;
}

i32 sami_engine_process_audio(
        struct sami_engine* engine,
        const f32* in,
        f32* out,
        u32 frames,
        u32 channels
) {
        u32 channel;
        u32 frame;
        for (frame = 0; frame < frames; ++frame) {
                for (channel = 0; channel < channels; ++channel) {
                        u32 index = (frame * channels) + channel;
                        float* out_channel =  &out[index];
                        float randomValue = 2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
                        *out_channel = randomValue * 0.5;
                }
        }
        return 0;
}

