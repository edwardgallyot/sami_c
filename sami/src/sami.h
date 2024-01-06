// Copyright 2023 edg

#pragma once

#include <stdbool.h>

#include "sami/src/engine/engine.h"
#include "utils/types.h"

struct sami_engine* sami_create_engine(void);

i32 sami_destroy_engine(struct sami_engine* engine);


void* sami_engine_reload(void* reload);

void* sami_engine_quit(void* engine);
