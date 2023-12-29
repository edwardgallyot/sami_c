add_library(atomic
STATIC
    src/atomic.c)

target_include_directories(atomic
PRIVATE
    ..
)
