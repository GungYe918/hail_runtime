# src/module/CMakeLists.txt

add_library(hail_module module.c)

target_include_directories(hail_module PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/wamr/include
)

