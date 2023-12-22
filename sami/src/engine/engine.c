// Copyright 2023 edg

#include <stdlib.h>

#include "src/engine/engine.h"
#include "src/state/state.h"

typedef struct sami_engine {
        sami_state* state;
} sami_engine;


sami_engine* sami_engine_create_engine() {
        sami_engine* engine = (sami_engine*)malloc(sizeof(sami_engine));
        return engine;
}

i32 sami_engine_free_engine(sami_engine* engine) {
        if (engine == NULL) 
                return -1;

        free(engine);
        return 0;
}
