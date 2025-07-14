#include <hail/sys/api/native_api.h>
#include <hail/common/config.h>
#include <wamr/include/wasm_export.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int hail_call_function(
    wasm_module_inst_t instance,
    const char *func_name,
    wasm_val_t *args,   
    uint32_t argc,
    wasm_val_t *rets,
    uint32_t retc,
    char *error_buf,
    uint32_t error_buf_size
) {
    wasm_function_inst_t func = wasm_runtime_lookup_function(instance, func_name);
    if (!func) {
        snprintf(error_buf, error_buf_size, "[Failed] no Function ( %s ) found\n", func_name);
        return -1;
    }


    wasm_exec_env_t exec_env = wasm_runtime_create_exec_env(instance, STACK_SIZE);
    if (!exec_env) {
        snprintf(error_buf, error_buf_size, "[Failed] create exec env failed: %s\n", error_buf);
        return -2;
    }

    bool ok = wasm_runtime_call_wasm_a(exec_env, func, retc, rets, argc, args);
#ifdef USE_DEBUG
    printf("[Debug] args[0] = %d, args[1] = %d\n", args[0].of.i32, args[1].of.i32);
    printf("[Debug] rets[0] = %d\n", rets[0].of.i32);
#endif
    wasm_runtime_destroy_exec_env(exec_env);
    
    if (!ok) {
        snprintf(error_buf, error_buf_size, "[Failed] function %s execute failed.\n", func_name);
        return -3;
    }

    return 0;
}
