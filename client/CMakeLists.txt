add_executable(client
    src/main.c
)

target_link_libraries(client
PRIVATE
    hot_reload
)

target_include_directories(client
PRIVATE
    ../lib
    ../sami
    ..
    .
)

add_custom_target(sami_client
    COMMAND ${CMAKE_COMMAND} -E echo "=== Running the 'run' executable ==="
    COMMAND client
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running the 'client' executable..."
)
