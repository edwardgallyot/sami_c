cmake_minimum_required(VERSION 3.10)  # Minimum version of CMake required

project(hot_reload)  # Name of your project

# Create a static library from hot_reload.c
add_library(hot_reload STATIC hot_reload.c)

target_link_libraries(hot_reload)

target_include_directories(hot_reload
PRIVATE
    ..
)

