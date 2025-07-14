# src/sys/wascall/CMakeLists.txt

add_library(hail_wascall 
    wascall_table.c
    default_calls.c
)

target_include_directories(hail_wascall PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/wamr/include
)

