# src/utils/CMakeLists.txt

add_library(hail_utils io.c)

target_include_directories(hail_utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/wamr/include
)