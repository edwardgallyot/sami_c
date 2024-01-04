// Copyright 2023 edg
#pragma once


#include "utils/types.h"


enum colour_id {
        colour_id_purple_fg = 1,
        colour_id_cyan_fg,
};


i32 init_colours(void);

void turn_colour_on(enum colour_id colour);

void turn_colour_off(enum colour_id colour);
