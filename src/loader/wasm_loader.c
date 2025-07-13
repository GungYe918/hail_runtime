#include <string.h>
#include <stdio.h>
#include <wamr/include/wasm_export.h>
#include <hail/loader/wasm_loader.h>


// dfdf
wasm_module_t
hail_load_module(const uint8_t *wasm_bytes, uint32_t size, 
                    char *error_buf, uint32_t error_buf_size) 
{
    return wasm_runtime_load(wasm_bytes, size, error_buf, error_buf_size);
}

wasm_module_inst_t 
hail_create_instance(wasm_module_t module, uint32_t stack_size, uint32_t heap_size, 
                        char *error_buf, uint32_t error_buf_size) 
{
    return wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, error_buf_size);
}

void 
hail_destroy_instance(wasm_module_inst_t instance) 
{
    if (!instance) {
        return;
    }

    wasm_runtime_deinstantiate(instance);
}

void 
hail_unload_module(wasm_module_t module) 
{
    if (!module) {
        return;
    }

    wasm_runtime_unload(module);
}