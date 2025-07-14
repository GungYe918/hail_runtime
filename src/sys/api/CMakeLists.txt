# src/sys/api/CMakeLists.txt

add_library(hail_api native_api.c)

option(HAIL_USE_DEBUG_MODE "Enable debug mode" OFF)

target_include_directories(hail_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib/wamr/include
)

if (HAIL_USE_DEBUG_MODE)
    message(STATUS "Debug Mode: ON")
    target_compile_definitions(hail_api PRIVATE USE_DEBUG)
else()
    message(STATUS "Debug Mode: OFF")
endif()