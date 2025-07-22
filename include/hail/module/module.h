#ifndef HAIL_MODULE_H
#define HAIL_MODULE_H

#include <stdint.h>
#include <wamr/include/wasm_export.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HAIL_MODULE_NONE = 0,
    HAIL_MODULE_LOADED,
    HAIL_MODULE_RUNNING,
    HAIL_MODULE_STOPPED,
    HAIL_MODULE_ERROR,
} hail_module_state_t;

typedef struct hail_module {
    /*  바이너리 데이터 정보  */
    uint8_t *wasm_data;                     // wasm 바이너리 시작 주소
    uint32_t wasm_size;                     // 바이너리 크기

    /*  WAMR 핸들  */
    wasm_module_t module;                   // 로드된 모듈
    wasm_module_inst_t module_inst;         // 모듈 인스턴스
    wasm_exec_env_t module_env;             // 모듈 env

    /*  상태 정보  */
    hail_module_state_t state;              // 현재 모듈 상태
    uint64_t version;                       // 버전 관리

    struct hail_module *next;               // 스케줄러용 모듈 체이닝
} __attribute__((packed)) hail_module_t;


// -------------------- //
// Hail 모듈 관리 함수들 //
// -------------------- //


/**
 * @brief Hail 모듈 시스템 초기화 함수
 * 
 * runtime init 시 호출되며 모듈이 로드될 환경을 초기화한다.
 * 모듈 에러 발생 시 전체 초기화가 필요한 경우에도 호출된다.
 * 
 * @param no 인자를 받지 않는다.
 * @return 성공시 0, 실패 시 음수를 반환한다.
 */
int hail_module_system_init(void);

/**
 * @brief Hail 모듈 로드 함수
 * 
 * .wasm및 .aot모듈을 로드하고 실행한다.
 * 
 * @param wasm_data 모듈 바이너리의 시작 주소 (.wasm or .aot)
 * @param wasm_size 모듈 바이너리 크기
 * 
 * @return 성공 시 hail_module_t*를 통해 로드에 성공한 모듈 포인터 반환, 실패 시 NULL 
 */
hail_module_t *hail_load_module(const uint8_t *wasm_data, uint32_t wasm_size);

/**
 * @brief Hail 모듈 언로드 함수
 * 
 * 특정 모듈의 메모리 값 해제 및 모든 내부 자원 정리
 */
int hail_unload_module(hail_module_t *mod);


/**
 * @brief Hail 모듈 실행 함수
 * 
 * 모듈의 기본 엔트리 함수(_start, 'main' 등)를 찾아 모듈을 실행
 * 
 * @param mod 실행할 모듈
 * @return 성공 시 0, 실패 시 음수 반환
 */
int hail_module_run(hail_module_t *mod);



#ifdef __cplusplus
}
#endif

#endif // HAIL_MODULE_H