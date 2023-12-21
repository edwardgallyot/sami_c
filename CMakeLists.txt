cmake_minimum_required(VERSION 3.0.0)
# Enable export of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sami_dev VERSION 1.0.0)

add_subdirectory(sami)
add_subdirectory(run)
