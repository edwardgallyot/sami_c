// Copyright 2023 edg

#include <stdio.h>

#include "src/sami.h"

int sami_init(bool say_hello) {
        if (say_hello)
                printf("Hello sami\n");

        return 0;
}
