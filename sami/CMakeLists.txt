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
    src/sami.c
    src/engine/engine.c
    src/state/state.c
)

target_include_directories(sami
PUBLIC
    ..
)

