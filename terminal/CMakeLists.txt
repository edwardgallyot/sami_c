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

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(terminal
    ${LIB_TYPE}
    src/terminal.c
    src/ui/ui.c
)

target_include_directories(terminal
PRIVATE
    ..
    ../lib/ncurses/include/
)

target_link_libraries(terminal
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/ncurses/lib/libncurses.a
    thread
    atomic
)
