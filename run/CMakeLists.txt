add_executable(run
    src/main.c
)

target_link_libraries(run
PRIVATE
    PortAudio
    portmidi
    hot_reload
)

target_include_directories(run
PRIVATE
    ..
    .
)

add_custom_target(sami_run
    COMMAND ${CMAKE_COMMAND} -E echo "=== Running the 'run' executable ==="
    COMMAND run
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running the 'run' executable..."
)
