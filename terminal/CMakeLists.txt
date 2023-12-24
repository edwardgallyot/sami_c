cmake_minimum_required(VERSION 3.10)
project(terminal)

option(
SAMI_HOT_RELOAD
    "Enable hot reloading for the SAMI library"
    OFF
)

if(SAMI_HOT_RELOAD)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()

add_library(terminal
    ${LIB_TYPE}
    src/terminal.c
)

target_include_directories(terminal
PRIVATE
    ..
    ../lib/ncurses/include/
)

target_link_libraries(terminal
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/ncurses/lib/libncurses.a
)