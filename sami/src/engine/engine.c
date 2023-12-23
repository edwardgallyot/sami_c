// Copyright 2023 edg

#include <stdio.h>
#include <stdlib.h>

#include "src/engine/engine.h"

sami_engine* sami_engine_create_engine() {
        sami_engine* engine = (sami_engine*)malloc(sizeof(sami_engine));

        if (engine == NULL)
                return engine;

        engine->state = sami_create_state();

        return engine;
}

i32 sami_engine_free_engine(sami_engine* engine) {
        if (engine == NULL) 
                return -1;

        i32 err;

        err = sami_destroy_state(engine->state);

        if (err != 0)
                return err;

        free(engine);

        return 0;
}
