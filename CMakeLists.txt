cmake_minimum_required(VERSION 3.6.0)
# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sami_dev VERSION 1.0.0)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SAMI_HOT_RELOAD ON CACHE BOOL "Enable sami hot reloading")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(SAMI_SOURCE
    ../sami/src/sami.c
    ../sami/src/engine/engine.c
    ../sami/src/state/state.c
)

add_subdirectory(lib/portaudio)
add_subdirectory(lib/portmidi)
add_subdirectory(sami)
add_subdirectory(run)
add_subdirectory(utils)
add_subdirectory(hot_reload)
