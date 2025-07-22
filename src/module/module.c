#include <hail/module/module.h>
#include <hail/common/config.h>
#include <hail/utils/stub.h>
#include <wamr/include/wasm_export.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

/**
 * @until .aot vs .wasm 모듈 판별 함수
 * 
 * 아래의 함수들은 module.c에서만 사용되는 aot포멧과 
 * wasm포멧을 구별하기 위한 내부 helper함수이다. 
 * 
 * @return bool값을 반환한다.
 */

static bool is_aot_format(const uint8_t *wasm_data, uint32_t wasm_size) {
    return (wasm_size >= 4 && (*(uint32_t *)wasm_data) == AOT_MAGIC);
}

static bool is_wasm_format(const uint8_t *wasm_data, uint32_t wasm_size) {
    return (wasm_size >= 4 && (*(uint32_t *)wasm_data) == WASM_MAGIC);
}


int hail_module_system_init(void) {    
    STUB();
    return 1;
}

hail_module_t *hail_load_module(const uint8_t *wasm_data, uint32_t wasm_size) {
    if (!wasm_data || wasm_size < 4) {
        printf("[Hail] Invalid state or data.\n");
        return NULL;
    }

    hail_module_t *mod = calloc(1, sizeof(hail_module_t));
    if (!mod) {
        printf("[Hail] out of memory.\n");
        return NULL;
    }

    mod->wasm_data = malloc(wasm_size);
    if (!mod->wasm_data) {
        free(mod);
        return NULL;
    }

    memcpy(mod->wasm_data, wasm_data, sizeof(wasm_size));
    mod->wasm_size = wasm_size;

    char error_buf[128] = {0};

    // mod->module에 모듈 연결
    if (is_wasm_format(wasm_data, wasm_size)) {
        printf("[Hail] .wasm format detected. \n");
        mod->module = wasm_runtime_load(mod->wasm_data, wasm_size, error_buf, sizeof(error_buf));
    } else if (is_aot_format(wasm_data, wasm_size)) {
        printf("[Hail] .aot format detected. \n");
        mod->module = wasm_runtime_load(mod->wasm_data, wasm_size, error_buf, sizeof(error_buf));
    } else {
        printf("[Hail] unknown or unsupported format. \n");
        return NULL;
    }

    if (!mod->module) {
        printf("[Hail] load error: %s\n", error_buf);
        goto fail;
    }

    // instance 생성
    mod->module_inst = 
        wasm_runtime_instantiate(mod->module, STACK_SIZE, HAIL_RUNTIME_HEAP_SIZE, error_buf, sizeof(error_buf));

    if (!mod->module_inst) {
        printf("[Hail] error at create instance: %s\n", error_buf);
        goto fail;
    }

    mod->module_env = 
        wasm_runtime_create_exec_env(mod->module_inst, STACK_SIZE);

    if (!mod->module_env) {
        printf("[Hail] error at create module_env: %s\n", error_buf);
        goto fail;
    }

    mod->state = HAIL_MODULE_LOADED;
    mod->version = 1;
    return mod;


    fail:
        if (mod->module_env) wasm_runtime_destroy_exec_env(mod->module_env);
        if (mod->module_inst) wasm_runtime_deinstantiate(mod->module_inst);
        if (mod->module) wasm_runtime_unload(mod->module);
        free(mod->wasm_data);
        free(mod);
        return NULL;

}

int hail_module_run(hail_module_t *mod) {
    if (!mod || mod->state != HAIL_MODULE_LOADED) {
        printf("[Hail] Module is not loaded. Module run failed.\n");
        return -1; 
    }

    wasm_function_inst_t func_inst = 
        wasm_runtime_lookup_function(mod->module_inst, "_start");
    if (!func_inst) {
        wasm_runtime_lookup_function(mod->module_inst, "main");
    }

    if (!func_inst) {
        printf("[Hail] No entry function (_start/main). \n");
        return -2;
    }

    bool ok = wasm_runtime_call_wasm(mod->module_env, func_inst, 0, NULL);
    if (!ok) {
        printf("[Hail] Run failed: %s\n", wasm_runtime_get_exception(func_inst));
        mod->state = HAIL_MODULE_ERROR;
        return -3;
    }

    mod->state = HAIL_MODULE_RUNNING;
    return 0;
}

int hail_unload_module(hail_module_t *mod) {
    if (!mod) {
        printf("[Hail] cannot find module.\n");
        return -1;
    }
    if (mod->module_env) {
        wasm_runtime_destroy_exec_env(mod->module_env);
    }  
    if (mod->module_inst) {
        wasm_runtime_deinstantiate(mod->module_inst);
    } 
    if (mod->module) {
        wasm_runtime_unload(mod->module);
    }      

    free(mod->wasm_data);
    free(mod);
    return 0;
}