# src/loader/CMakeLists.txt

add_library(hail_loader wasm_loader.c)

target_include_directories(hail_loader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/wamr/include
)

