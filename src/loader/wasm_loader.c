#include <string.h>
#include <stdio.h>
#include <wamr/include/wasm_export.h>
#include <wamr/include/aot_export.h>
#include <hail/loader/wasm_loader.h>


wasm_module_t
hail_load_module(uint8_t *wasm_bytes, uint32_t size, 
                 char *error_buf, uint32_t error_buf_size) 
{
    if (size < 4) {
        printf("[Failed] Buffer too small. hail_load_module failed.\n");
        snprintf(error_buf, error_buf_size,
                 "WASM module load failed: buffer too small (%u bytes)", size);
        return NULL;
    }

    uint32_t magic = *(uint32_t *)wasm_bytes;

    if (magic == WASM_MAGIC) {
        printf("[Info] Detected WASM binary format.\n");
        return wasm_runtime_load(wasm_bytes, size, error_buf, error_buf_size);
    } 
    else if (magic == AOT_MAGIC) {
        printf("[Info] Detected AOT binary format.\n");
        return wasm_runtime_load(wasm_bytes, size, error_buf, error_buf_size);
    }
    else {
        printf("[Failed] Unknown magic number 0x%08x. hail_load_module failed\n", magic);
        snprintf(error_buf, error_buf_size,
                 "WASM module load failed: unknown magic header 0x%08x", magic);
        return NULL;
    }
}

wasm_module_inst_t 
hail_create_instance(wasm_module_t module, uint32_t stack_size, uint32_t heap_size, 
                        char *error_buf, uint32_t error_buf_size) 
{
    if (!module) {
        printf("[Failed] module is NULL. hail_create_instance failed.\n");
        return NULL;
    }
    return wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, error_buf_size);
}

void 
hail_destroy_instance(wasm_module_inst_t instance) 
{
    if (!instance) {
        printf("[Failed] no instance found. hail_destroy_instance failed.\n");
        return;
    }

    wasm_runtime_deinstantiate(instance);
}

void 
hail_unload_module(wasm_module_t module) 
{
    if (!module) {
        printf("[Failed] no module found. hail_unload_module failed.\n");
        return;
    }

    wasm_runtime_unload(module);
}