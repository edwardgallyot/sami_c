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

add_library(
sami
    ${LIB_TYPE}
    ${SAMI_SOURCE}
)

target_link_libraries(sami
PRIVATE
    utils
)

target_include_directories(sami
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    .
    ..
)

