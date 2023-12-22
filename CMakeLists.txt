cmake_minimum_required(VERSION 3.6.0)
# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sami_dev VERSION 1.0.0)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SAMI_HOT_RELOAD ON CACHE BOOL "Enable sami hot reloading")

add_subdirectory(lib/portaudio)
add_subdirectory(lib/portmidi)
add_subdirectory(sami)
add_subdirectory(run)
