#ifndef HAIL_WASCALL_H
#define HAIL_WASCALL_H

#include <stdint.h>

// wascall 함수 handler type
typedef int32_t (*wascall_handler_t)(int32_t *args, int32_t *rets);

/**
 * @brief wascall index
 * 
 * 이 인덱스 값은 wasm에서 syscall을 호출하기 위한 wascall에서 사용되는 인덱스 값이다. 
 * syscall 방식과 유사하게 dispatcher방식을 사용하며 인덱스에 따라서 해당 wascall 실행 함수로 점프한다.
 */

#define WASCALL_WRITE  0
#define WASCALL_READ   1
#define WASCALL_EXIT   2
#define WASCALL_MAX    30

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 사용자 정의 wascall을 등록
 * 
 * @param wascall_id hail_runtime에서 사용하고자 하는 wascall_id
 * @param handler wascall 함수 handler
 */
void wascall_register(uint32_t wascall_id, wascall_handler_t handler);

/**
 * @brief wascall 호출 인터페이스
 * 
 * @param wascall_id hail_runtime에서 사용하고자 하는 wascall_id
 * @param args
 * @param rets
 */
int32_t wascall_dispatch(uint32_t wascall_id, int32_t *args, int32_t *rets);


wascall_handler_t wascall_get_handler(uint32_t wascall_id);


#ifdef __cplusplus
}
#endif

#endif // HAIL_WASCALL_H