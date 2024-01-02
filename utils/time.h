// Copyright 2023 edg
//

#pragma once

#include <time.h>

#include "utils/types.h"

i32 sleep_ns(u64 ns);

i32 sleep_ns(u64 ns) {
        struct timespec req, rem;

        const u64 ns_max = 1000000000;

        req.tv_sec = ns / ns_max;
        req.tv_nsec = ns % ns_max;

        while (nanosleep(&req, &rem) < 0)
                req = rem;

        return 0;
}
