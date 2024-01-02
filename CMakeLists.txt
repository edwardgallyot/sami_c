cmake_minimum_required(VERSION 3.6.0)
# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

project(sami_dev VERSION 1.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)


set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

set(SAMI_HOT_RELOAD ON CACHE BOOL "Enable sami hot reloading")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()


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
