# Create a static library from hot_reload.c
add_library(hot_reload
STATIC
    src/hot_reload.c)

target_link_libraries(hot_reload
PRIVATE
)

target_include_directories(hot_reload
PRIVATE
    ..
)

