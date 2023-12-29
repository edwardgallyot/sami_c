// Copyright 2023 edg

#pragma once

#include <stdbool.h>

#include "utils/types.h"

// Typedefs for atomic types
typedef int atomic_i32;
typedef unsigned int atomic_u32;
typedef float atomic_f32;
typedef bool atomic_bool;

// Function declarations for atomic load and store operations
i32 atomic_load_i32(atomic_i32 *obj);
void atomic_store_i32(atomic_i32 *obj, i32 val);

u32 atomic_load_u32(atomic_u32 *obj);
void atomic_store_u32(atomic_u32 *obj, u32 val);

f32 atomic_load_f32(atomic_f32 *obj);
void atomic_store_f32(atomic_f32 *obj, f32 val);

bool atomic_load_bool(atomic_bool *obj);
void atomic_store_bool(atomic_bool *obj, bool val);
