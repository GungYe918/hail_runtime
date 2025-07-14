#ifndef HAIL_CONFIG_H
#define HAIL_CONFIG_H

/*  wasm magic number   */
#define WASM_MAGIC 0x6d736100  // "\0asm" 
#define AOT_MAGIC  0xdeadbeef  // AOT magic


#ifndef HAIL_RUNTIME_HEAP_SIZE
#pragma message("Info: HAIL_RUNTIME_HEAP_SIZE not defined. Default heap size (2MB) will be used.")
#define HAIL_RUNTIME_HEAP_SIZE (2 * 1024 * 1024)
#endif

#ifndef STACK_SIZE
#define STACK_SIZE (64 * 1024)
#endif


#endif