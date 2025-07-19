#include <hail/sys/wascall/wascall.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
    // Step 1: 기본 핸들러 테이블 초기화
    if (wascall_table_init() != 0) {
        printf("[Test] wascall table init failed.\n");
        return 1;
    }

    // Step 2: 출력할 메시지 준비
    const char *msg = "Hello from wascall_write!\n";
    size_t len = strlen(msg);
    intptr_t ptr = (intptr_t)msg;

    // Step 3: 포인터를 32비트로 분리
    int32_t low  = (int32_t)(ptr & 0xFFFFFFFF);
    int32_t high = (int32_t)(ptr >> 32);

    int32_t written = 0;

    // Step 4: wascall_write 호출
    int ret = wascall(WASCALL_WRITE,
                      1,        // fd (stdout)
                      low,      // low 32-bit of pointer
                      high,     // high 32-bit of pointer
                      (int32_t)len,  // length
                      &written);     // return value pointer

    // Step 5: 결과 확인
    if (ret == 0) {
        printf("[Test] wascall_write success. Bytes written: %d\n", written);
    } else {
        printf("[Test] wascall_write failed with ret = %d\n", ret);
    }

    return 0;
}
