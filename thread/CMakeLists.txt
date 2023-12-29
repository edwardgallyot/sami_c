set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(thread
STATIC
    src/thread.c)

target_link_libraries(thread
PRIVATE
    pthread
)

target_include_directories(thread
PRIVATE
    ..
)
