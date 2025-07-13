# src/runtime/CMakeLists.txt

# heap 할당 관련 옵션 
option(HAIL_USE_STATIC_HEAP "Use static heap buffer" ON)
set(HAIL_RUNTIME_HEAP_SIZE "2097152" CACHE STRING "Heap size in bytes (default: 2MB)")

# [dir] runtime 내부 빌드
add_library(hail_runtime runtime.c)

# include 폴더 설정
target_include_directories(hail_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib/wamr/include
)

# 옵션 정의를 컴파일러에 전달
target_compile_definitions(hail_runtime PRIVATE
    HAIL_RUNTIME_HEAP_SIZE=${HAIL_RUNTIME_HEAP_SIZE}
)

if (HAIL_USE_STATIC_HEAP)
    target_compile_definitions(hail_runtime PRIVATE USE_STATIC_HEAP)
endif()