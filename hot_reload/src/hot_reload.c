// Copyright 2023 edg

#include <bits/types/struct_timeval.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#include "hot_reload/src/hot_reload.h"
#include "utils/log.h"

enum hot_reload_action {
        hot_reload_err = -1,
        hot_reload_nothing = 0,
        hot_reload_quit = 1,
        hot_reload_reload = 2,
};

static void* lib_handle = NULL;

typedef void* (*shared_func)(void*);

shared_func func;

static i32 handle_lib_function(struct hot_reloader* hot_reloader, const char* name) {
        if (name == NULL) {
                ERROR("Lib name.");
                return -1;
        }

        if (hot_reloader == NULL) {
                ERROR("No hot reloader supplied");
                return -1;
        }

        i32 err = 0;


        if (lib_handle == NULL) {
                lib_handle = dlopen(hot_reloader->file, (RTLD_LAZY | RTLD_LOCAL));
        }

        if (!lib_handle) {
                ERROR("No lib handle at: %p", lib_handle);
                return -1;
        }

        *(void **) (&func)  = dlsym(lib_handle, name);

        if (func) {
                hot_reloader->data = func(hot_reloader->data);
        } else {
                ERROR("No function loaded: %s", dlerror());
                err = -1;
        }

        return err;
}


static char handle_stdin() {
        char input[256];

        memset(input, 0, sizeof(input));

        if (fgets(input, sizeof(input), stdin) == NULL) {
                return 0;
        }
        if (input[0] == 'q') {
                return 'q';
        }

        if (input[0] == 'l') {
                return 'l';
        }

        return 0;
}

static enum hot_reload_action check_for_changes_in_watch_list(struct hot_reloader* reloader) {
        watch_list_item* item = reloader->watch_list;


        struct stat stats;

        bool has_stats_changed = false;
        while (item != NULL) {
                watch_list_item* next = item->next;

                if (stat(item->file_path, &stats) == -1) {
                        ERROR("Error getting file stats: %d", errno);
                        return hot_reload_nothing;
                }

                if ((i64)stats.st_mtime != (i64)item->last_stats.st_mtime) {
                        printf("%s: changed!\n", item->file_path);
                        has_stats_changed = true;
                }

                item->last_stats = stats;

                item = next;
        }

        if (has_stats_changed)
                return hot_reload_reload;
        else
                return hot_reload_nothing;
}

static enum hot_reload_action handle_file_changes(struct hot_reloader* reloader) {
        sleep(1);
        return check_for_changes_in_watch_list(reloader);
}

static enum hot_reload_action run_main_loop(struct hot_reloader* reloader) {
        i32 err = 0;

        if (err != 0)
                return err;


        enum hot_reload_action action = handle_file_changes(reloader);

        switch (action) {
        case hot_reload_quit:
                err = handle_lib_function(reloader, reloader->destroy);

                if (err == 0) {
                        return hot_reload_quit;
                } else {
                        ERROR("Error handling destory_func: %d", err);
                        return hot_reload_err;
                }
        case hot_reload_reload:
                if (reloader->on_reload)
                        reloader->on_reload();

                if (system(reloader->build) != 0) {
                        ERROR("Issue with build: %s", reloader->build);
                        return hot_reload_nothing;
                }

                err = handle_lib_function(reloader, reloader->destroy);

                if (err != 0) {
                        ERROR("Error handling lib function: %d", err);
                        return hot_reload_nothing;
                }


                if (dlclose(lib_handle) == 0) {
                        lib_handle = NULL;
                        reloader->data = NULL;
                } else {
                        ERROR("Couldn't close dl: %d: %s", err, dlerror());
                }

                err = handle_lib_function(reloader, reloader->load);

                if (reloader->on_reloaded)
                        reloader->on_reloaded();


                if (err == 0) {
                        // We've just reloaded so return nothing
                        return hot_reload_nothing;
                } else {
                        ERROR("Error handling load_func: %d", err);
                        return hot_reload_err;
                }
        default:
                return hot_reload_nothing;
        }
}


i32 init_hot_reloader(struct hot_reloader* reloader) {
        return handle_lib_function(reloader, reloader->load);
}

i32 run_hot_reloader(struct hot_reloader* reloader) {
        while (true) {
                enum hot_reload_action action = run_main_loop(reloader);

                if (action == hot_reload_quit)
                        break;
                else if (action == hot_reload_err)
                        return -1;
                else
                        continue;
        }
        return 0;
}

i32 add_file_to_watch_list(struct hot_reloader* reloader, const char* file_path) {
        i32 fd = open(file_path, (O_RDWR));
        if (fd == -1) {
                ERROR("Error opening file_path: %s: %d", file_path, fd);
                return fd;
        }

        i32 err = close(fd);
        if (err == -1) {
                ERROR("Error closing up fd: %d.", errno);
                return fd;
        }

        watch_list_item* new_item = reloader->watch_list;

        if (new_item == NULL) {
                reloader->watch_list = malloc(sizeof(watch_list_item));

                if (reloader->watch_list == NULL) {
                        ERROR("Error allocating memory.");
                        return -1;
                }
                new_item = reloader->watch_list;
        } else {
                watch_list_item* item = NULL;

                while (new_item != NULL) {
                        item = new_item;
                        new_item = item->next;
                }

                item->next = malloc(sizeof(watch_list_item));

                if (item->next == NULL) {
                        ERROR("Error allocating memory");
                        return -1;
                }

                new_item = item->next;
        }

        new_item->file_path = file_path;
        new_item->next = NULL;

        if (stat(new_item->file_path, &new_item->last_stats) != 0) {
                ERROR("Error getting stats using fstat: %d", errno);
                free(new_item);
                return -1;
        }

        return 0;
}

i32 clean_hot_reloader(struct hot_reloader* reloader) {
        if (reloader == NULL) {
                return -1;
        }

        if (lib_handle) {
                dlclose(lib_handle);
        }

        watch_list_item* item = reloader->watch_list;

        while (item != NULL) {
                watch_list_item* next = item->next;
                free(item);
                item = next;
        }

        return 0;
}
