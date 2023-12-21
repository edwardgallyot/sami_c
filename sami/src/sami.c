// Copyright 2023 edg

#include "src/sami.h"

sami_engine* sami_create_engine() {
        return sami_engine_create_engine();
}
i32 sami_destroy_engine(sami_engine* engine) {
        return sami_engine_free_engine(engine);
}

