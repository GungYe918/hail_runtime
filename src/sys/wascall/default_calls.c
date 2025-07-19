#include <hail/sys/wascall/wascall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int32_t wascall_write(int32_t *args, int32_t *rets) {
    int fd = args[0];

    // 포인터 재조합
    intptr_t ptr_val = ((intptr_t)(uint32_t)args[1]) |
                       (((intptr_t)(uint32_t)args[2]) << 32);
    const char *buf = (const char *)ptr_val;

    int len = args[3];
    int written = write(fd, buf, len);

    if (rets)
        rets[0] = written;

    return (written < 0) ? -1 : 0;
}

static int32_t wascall_read(int32_t *args, int32_t *rets) {
    int fd = args[0];
    char *buf = (char *)(uintptr_t)args[1];
    int len = args[2];
    int read_len = read(fd, buf, len);
    if (rets) rets[0] = read_len;
    return (read_len < 0) ? -1 : 0;
}

static int32_t wascall_exit(int32_t *args, int32_t *rets) {
    exit(args[0]);
    return 0;       // 도달 안함
}

static const wascall_entry_t default_wascall_table[WASCALL_MAX] = {
    [WASCALL_WRITE] = {wascall_write,   4},
    [WASCALL_READ]  = {wascall_read,    3},
    [WASCALL_EXIT]  = {wascall_exit,    1},
    /*
        TODO: 추가적인 wascall 구현, 나머지는 NULL
    */
};

// wascall_table_init함수용 getter - 이 함수를 통해서 기본 wascall테이블 복사
const wascall_entry_t *get_default_handler_table(void) {
    return default_wascall_table;
}