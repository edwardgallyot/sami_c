cmake_minimum_required(VERSION 3.6.0)
# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

project(sami_dev VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


# Directory where the ncurses static library should be
set(NCURSES_LIB_DIR "${CMAKE_BINARY_DIR}/../lib/ncurses")
set(NCURSES_STATIC_LIB "${NCURSES_LIB_DIR}/lib/libncurses.a")

# Try to find the ncurses static library
find_library(NCURSES_FOUND NAMES ncurses libncurses.a PATHS ${NCURSES_LIB_DIR} NO_DEFAULT_PATH)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT NCURSES_FOUND)
    # Define the steps to build ncurses

    # Custom command to build ncurses
    add_custom_command(
        OUTPUT ${NCURSES_STATIC_LIB}
        COMMAND cd ${NCURSES_LIB_DIR} && ./configure --with-static --with-pic --without-normal --without-debug CFLAGS=-fPIC
        COMMAND make -C ${NCURSES_LIB_DIR}
        COMMENT "Building ncurses"
    )

    # Custom target that depends on the custom command
    add_custom_target(ncurses ALL DEPENDS ${NCURSES_STATIC_LIB})

    # Define the static library target
    add_library(libncurses STATIC IMPORTED)
    set_property(TARGET libncurses PROPERTY IMPORTED_LOCATION ${NCURSES_STATIC_LIB})
    add_dependencies(libncurses ncurses)
else()
    add_library(libncurses STATIC IMPORTED)
    set_property(TARGET libncurses PROPERTY IMPORTED_LOCATION ${NCURSES_FOUND})
endif()
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SAMI_HOT_RELOAD ON CACHE BOOL "Enable sami hot reloading")

set(PA_USE_JACK ON CACHE BOOL "Enable sami hot reloading")
set(PA_USE_PULSE_AUDIO ON CACHE BOOL "Enable sami hot reloading")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

add_subdirectory(lib/portaudio)
add_subdirectory(lib/portmidi)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(sami)
add_subdirectory(run)
add_subdirectory(hot_reload)
add_subdirectory(terminal)
add_subdirectory(client)
add_subdirectory(thread)
add_subdirectory(atomic)
