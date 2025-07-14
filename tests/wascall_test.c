#include <stdio.h>
#include <stdlib.h>
#include <hail/sys/wascall/wascall.h>
#include <string.h>

int main(void) {
    const char *msg = "Hello from wascall write!\n";
    int32_t args[4];

    args[0] = 1; // fd

    // 포인터를 32비트 2개로 분할
    intptr_t ptr_val = (intptr_t)msg;
    args[1] = (int32_t)(ptr_val & 0xFFFFFFFF);         // 하위
    args[2] = (int32_t)((ptr_val >> 32) & 0xFFFFFFFF); // 상위

    args[3] = strlen(msg); // len

    int32_t rets[1] = {0};

    int32_t result = wascall_dispatch(WASCALL_WRITE, args, rets);
}