cmake_minimum_required(VERSION 3.10)

# Project Name
project(utils)

# Create a static library 'utils'
add_library(utils STATIC
    log.c
)

# Include directories
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
