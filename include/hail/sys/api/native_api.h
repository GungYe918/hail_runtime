#ifndef HAIL_NATIVE_API_H
#define HAIL_NATIVE_API_H

#include <wamr/include/wasm_export.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
    
int32_t hail_call_function(
    wasm_module_inst_t inst,
    const char *func_name,
    wasm_val_t *args,   
    uint32_t argc,
    wasm_val_t *rets,
    uint32_t retc,
    char *error_buf,
    uint32_t error_buf_size
);

#ifdef __cplusplus
}
#endif

#endif