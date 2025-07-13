#ifndef HAIL_WASM_LOADER_H
#define HAIL_WASM_LOADER_H

#include <stdint.h>
#include <wamr/include/wasm_export.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief runtime에서의 모듈 로드 함수
 * 
 * wasm 모듈을 특정 메모리 주소에 로드하는 함수이다. 
 * 
 * @param wasm_bytes @param size
 * @param error_buf @param error_buf_size
 *  
 */
wasm_module_t hail_load_module(const uint8_t *wasm_bytes, uint32_t size, 
                                    char *error_buf, uint32_t error_buf_size);
                                    
/**
 * @brief wasm모듈 instance 생성 함수
 * 
 * wasm모듈 로드를 위한 인스턴스를 생성하는 함수이다.
 * 
 * @param module @param stack_size @param heap_size
 * @param error_buf @param error_buf_size
 */
wasm_module_inst_t hail_create_instance(wasm_module_t module, uint32_t stack_size, uint32_t heap_size, 
                                                char *error_buf, uint32_t error_buf_size);

/**
 * @brief wasm 모듈 instance 제거 함수
 * @param instance
 */                                            
void hail_destroy_instance(wasm_module_inst_t instance);

/**
 * @brief wasm 모듈 언로드 함수
 * @param module
 */
void hail_unload_module(wasm_module_t module);

#ifdef __cplusplus
}
#endif

#endif // HAIL_WASM_LOADER_H