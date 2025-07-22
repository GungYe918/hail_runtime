cmake_minimum_required(VERSION 3.13)
project(hail_runtime C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 테스트용 실행파일
add_executable(hail_test
    src/main.c
)

# runtime 라이브러리 포함 (src/runtime/CMakeLists.txt)
add_subdirectory(src/runtime)
add_subdirectory(src/loader)
add_subdirectory(src/utils)
add_subdirectory(src/sys/api)
add_subdirectory(src/module)
add_subdirectory(src/sys/wascall)



# WAMR 및 기타 라이브러리 연결
target_link_libraries(hail_test
    hail_runtime
    hail_loader
    hail_module
    hail_utils
    hail_api
    hail_wascall
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/wamr/libiwasm.a
    m
)