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

/*  wascall 메타데이터 테이블  */
typedef struct {
    wascall_handler_t handler;
    uint8_t argc;   // wascall이 요구하는 i32인자 개수
} wascall_entry_t;

/**
 * @brief 사용자 정의 wascall을 등록
 * 
 * 시스템 full_init시 내부 정적 테이블에 wascall을 등록.
 * 런타임 내부에서 정의된 wascall은 모두 등록이 진행되며 사용자가 등록하는 경우는 제한됨.
 * 
 * @param wascall_id 등록할 함수 index
 * @param handler 실행할 함수 포인터
 * 
 * 성공 시 0, 실패 시 음수 반환
 */
int wascall_register(uint32_t wascall_id, wascall_handler_t handler);

/**
 * @brief wascall 호출 인터페이스
 * 
 * 최대 8개의 인자 + 선택적 결과 포인터를 전달받아 지정된 wascall을 실행.
 * rets가 필요한 경우 포인터를 인자에 포함해 전달해야 함.
 * 
 * @param wascall_id wascall 호출 번호
 * @param ... 최대 8개의 int32_t 인자 + rets (Option)
 * @return 성공 시 i32값, 실패 시 음수 반환
 */
int32_t wascall(uint32_t wascall_id, ...);

/**
 * @brief 내부 handler getter (외부에서는 작동 X)
 * 
 * @param wascall_id wascall 호출 번호
 */
wascall_handler_t wascall_get_handler(uint32_t wascall_id);

/**
 * @brief wascall 테이블 초기화 함수
 * 
 * @return 성공시 0, 실패 시 음수 반환
 */
int wascall_table_init(void);


#ifdef __cplusplus
}
#endif

#endif // HAIL_WASCALL_H