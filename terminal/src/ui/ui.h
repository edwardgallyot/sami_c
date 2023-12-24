// Copyright 2023 edg

#include "utils/types.h"

typedef struct ui {
        int counter; 
} ui; 


ui* terminal_build_ui();

i32 terminal_run_ui(ui* ui);

i32 terminal_destroy_ui(ui* ui);

