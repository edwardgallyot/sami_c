// Copyright 2024 edg

#include <stdlib.h>

#include "terminal/src/ui/layout/layout.h"
#include "terminal/src/ui/window/window.h"
#include "utils/log.h"

struct layout* create_layout(void) {
        struct layout* layout = malloc(sizeof(struct layout));

        if (layout == NULL) {
                ERROR("Couldn't allocate layout");
                return NULL; 
        }

        layout->main = NULL;
        return layout; 
}

i32 destroy_layout(struct layout* layout) {
        if (layout == NULL) {
                ERROR("Passed NULL layout");
                return -1;
        }
        if (layout->main != NULL) {

        }
        free(layout);
        return 0;
}

i32 update_layout_from_state(struct layout* layout, struct state* state) {
        if (layout->main == NULL) {
                layout->main = create_window();
                if (layout->main == NULL) {
                        return -1;
                }
        }

        window_update_dimensions(
                layout->main,
                state->height / 2,
                state->width / 2,
                state->cursor_position_y / 2,
                state->cursor_position_x / 2
        );

        refresh_window(layout->main);
        
        return 0;
}
