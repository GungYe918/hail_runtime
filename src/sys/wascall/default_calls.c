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

wascall_handler_t get_default_handler(uint32_t id) {
    switch (id) {
        case WASCALL_WRITE: return wascall_write;
        case WASCALL_READ:  return wascall_read;
        case WASCALL_EXIT:  return wascall_exit;
        default: return NULL;
    }
}