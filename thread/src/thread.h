// Copyright 2023 edg

#pragma once

#include "utils/types.h"

struct thread;

struct thread* create_thread(const char *name, void* (*function)(void *), void *arg);
i32 join_thread(struct thread* thread);

struct mutex;

struct mutex* init_mutex();
i32 lock_mutex(struct mutex* mutex);
i32 unlock_mutex(struct mutex* mutex);
i32 destroy_mutex(struct mutex* mutex);
