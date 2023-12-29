#include "atomic/src/atomic.h"

// Implementations for atomic operations on int
i32 atomic_load_i32(atomic_i32 *obj) {
        return __sync_fetch_and_add(obj, 0);
}

void atomic_store_i32(atomic_i32 *obj, i32 val) {
        __sync_lock_test_and_set(obj, val);
}

// Implementations for atomic operations on unsigned int
u32 atomic_load_u32(atomic_u32 *obj) {
        return __sync_fetch_and_add(obj, 0);
}

void atomic_store_u32(atomic_u32 *obj, u32 val) {
        __sync_lock_test_and_set(obj, val);
}

// Implementations for atomic operations on float
// Using a union for type punning
union FloatCast {
        atomic_f32 f;
        atomic_i32 i;
};

f32 atomic_load_f32(atomic_f32 *obj) {
        union FloatCast cast;
        cast.i = __sync_fetch_and_add((atomic_i32 *)obj, 0);
        return cast.f;
}

void atomic_store_f32(atomic_f32 *obj, f32 val) {
        union FloatCast cast;
        cast.f = val;
        __sync_lock_test_and_set((atomic_i32 *)obj, cast.i);
}

// Implementations for atomic operations on bool
bool atomic_load_bool(atomic_bool *obj) {
        return __sync_fetch_and_add((atomic_i32*)obj, 0);
}

void atomic_store_bool(atomic_bool *obj, bool val) {
        __sync_lock_test_and_set(obj, val);
}
