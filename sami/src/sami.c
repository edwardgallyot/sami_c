// Copyright 2023 edg

#include "src/sami.h"
#include <stdio.h>

i32 sami_init() {
        printf("Init sami!\n");
        return 0;
}

sami_engine* sami_create_engine() {
        return sami_engine_create_engine();
}
i32 sami_destroy_engine(sami_engine* engine) {
        return sami_engine_free_engine(engine);
}

void* sami_engine_reload(void* engine) {
        printf("just loading my tings.\n");

        if (engine != NULL)
                sami_destroy_engine(engine);

        return sami_create_engine();
}
