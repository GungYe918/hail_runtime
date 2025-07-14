#ifndef RUNTIME_H
#define RUNTIME_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief runtime 초기화 함수
 * 
 * Hail runtime을 최초로 초기화하고 메모리 할당을 진행하는 함수이다.
 * malloc의 실패시 -1, wasm_runtime_full_init이 최종 실패 시 -2를 반환한다.
 */
int runtime_init();

#ifdef __cplusplus
}
#endif

#endif // RUNTIME_H