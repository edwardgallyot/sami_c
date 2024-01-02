// Copyright 2023 edg

#pragma once

#include <stdio.h>

// ERROR macro
#define ERROR(format, ...)                                     {\
        fprintf(stderr,                                         \
                "[%s %s] ERROR at %s:%d in %s(): "format,       \
                __DATE__,                                       \
                __TIME__,                                       \
                __FILE__,                                       \
                __LINE__,                                       \
                __func__,                                       \
                ##__VA_ARGS__);                                 \
        fprintf(stderr, "\n");                                  }
