// Copyright 2023 edg

#pragma once

#include <stdbool.h>

#include "src/engine/engine.h"
#include "utils/types.h"

/** @brief creates a sami_engine
 *
 * @returns a pointer to a sami engine.
 * NULL if not allocated.
 **/
sami_engine* sami_create_engine();

/** @brief destroys the sami_engine
 *
 * This function can only fail on a null pointer
 * being passed.
 *
 * If free fails it is marked throw, so that 
 * will more than likely be a SIG. TODO: What is it?
 *
 * @param the engine to destroy
 *
 * @returns i32 -1 if unsuccessful and 
 * returns 0 if successful.
 **/
i32 sami_destroy_engine(sami_engine* engine);


/*
 * @brief reloads the engine from either a nullptr or a pointer
 *
 **/
void* sami_engine_reload(void* reload);

void* sami_engine_quit(void* engine);
