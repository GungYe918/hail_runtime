#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hail/runtime/runtime.h>
#include <wamr/include/wasm_export.h>

#ifndef HAIL_RUNTIME_HEAP_SIZE
#warning "HAIL_RUNTIME_HEAP_SIZE not defined. Using default 2MB."
#define HAIL_RUNTIME_HEAP_SIZE (2 * 1024 * 1024)
#endif

#ifndef STACK_SIZE
#define STACK_SIZE (64 * 1024)
#endif

static uint8_t *internal_heap_buf = NULL;

int runtime_init(void) {
    RuntimeInitArgs init_args = {0};
    uint8_t* heap_buf = NULL;
    uint32_t heap_size = HAIL_RUNTIME_HEAP_SIZE;

#ifdef USE_STATIC_HEAP
    static uint8_t static_heap_buf[HAIL_RUNTIME_HEAP_SIZE];
    heap_buf = static_heap_buf;
#else
    internal_heap_buf = malloc(heap_size);
    if (!internal_heap_buf) {
        printf("[Failed] malloc failed\n");
        return -1;
    }

    heap_buf = internal_heap_buf;
#endif

    init_args.mem_alloc_type = Alloc_With_Pool;    
    init_args.mem_alloc_option.pool.heap_buf = heap_buf;
    init_args.mem_alloc_option.pool.heap_size = heap_size;

    if (!wasm_runtime_full_init(&init_args)) {
        printf("[Failed] wasm_runtime_full_init failed\n");
#ifndef USE_STATIC_HEAP
        free(internal_heap_buf);
        internal_heap_buf = NULL;
#endif
        return -2;
    }


   printf("[Hail] runtime initialized successfully. Heap size: %u\n", heap_size);

    // TODO::load_module

    return 0;
    
}
