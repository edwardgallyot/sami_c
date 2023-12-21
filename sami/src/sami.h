// Copyright 2023 edg

#pragma once

#include <stdbool.h>

#include "src/engine/engine.h"
#include "utils/types.h"

sami_engine* sami_create_engine();

/*
 * Returns -1 if unsuccessful and 
 * returns 0 if successful.
 *
 * This function can only fail on a null pointer
 * being passed.
 *
 * If free fails it is marked throw, so that 
 * will more than likely be a SIG. TODO: What is it?
 */
i32 sami_destroy_engine(sami_engine* engine);
