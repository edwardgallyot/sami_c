// Copyright 2023 edg

#include <pthread.h>
#include <stdlib.h>

#include "thread/src/thread.h"
#include "utils/log.h"

struct thread {
        pthread_t id;
        const char* name;
};

struct thread* create_thread(const char *name, void *(*function)(void *), void *arg) {
        struct thread* new_thread = (struct thread*)malloc(sizeof(struct thread));
        if (new_thread == NULL) {
                ERROR("Couldn't allocate new thread");
                return NULL;
        }

        new_thread->name = name;
        i32 err = pthread_create(&new_thread->id, NULL, function, arg);
        if (err != 0) {
                ERROR("Couldn't create new thread: %d", err);
                free(new_thread);
                return NULL;
        }

        return new_thread;
}

i32 join_thread(struct thread* thread) {
        if (thread == NULL) {
                return -1;
        }

        i32 err = pthread_join(thread->id, NULL);
        if (err != 0) {
                ERROR("Couldn't join thread: %d", err);
                return -1;
        }

        free(thread);
        return err;
}


struct mutex {
        pthread_mutex_t lock;
};

struct mutex* init_mutex() {
        struct mutex* new_mutex = malloc(sizeof(struct mutex));
        if (new_mutex == NULL) {
                ERROR("malloc failed");
                return NULL;
        }

        i32 err = pthread_mutex_init(&new_mutex->lock, NULL);
        if (err != 0) {
                ERROR("pthread_mutex_init failed: %d", err);
                free(new_mutex);
                return NULL;
        }

        return new_mutex;
}

i32 lock_mutex(struct mutex* mutex) {
        if (mutex == NULL) {
                return -1;
        }

        i32 err = pthread_mutex_lock(&mutex->lock);
        if (err != 0) {
                ERROR("Error locking mutex: %d", err);
        }

        return err;
}

i32 unlock_mutex(struct mutex* mutex) {
        if (mutex == NULL) {
                return -1;
        }

        i32 err = pthread_mutex_unlock(&mutex->lock);
        if (err != 0) {
                ERROR("Error unlocking mutex: %d", err);
        }

        return err;
}

i32 destroy_mutex(struct mutex* mutex) {
        if (mutex == NULL) {
                return -1;
        }

        i32 err = pthread_mutex_destroy(&mutex->lock);
        if (err != 0) {
                ERROR("Error destroying mutex: %d", err);
        }

        return err;
}


// TODO(edg): Win32 impl
