// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>

#include "src/engine/engine.h"
#include "utils/log.h"

static void process_sami_audio(f32** buffer, u32 num_samples, u32 num_channels) {
}

struct sami_engine* sami_engine_create_engine() {
        struct sami_engine* engine = malloc(sizeof(struct sami_engine));

        if (engine == NULL)
                return engine;

        engine->state = sami_create_state();
        engine->on_audio_callback = process_sami_audio;

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
