#include <hail/sys/wascall/wascall.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CALLS WASCALL_MAX

static wascall_handler_t wascall_table[MAX_CALLS] = { 0 };

wascall_handler_t wascall_get_handler(uint32_t wascall_id) {
    if (wascall_id >= MAX_CALLS) {
        printf("[Failed] wrong id. wascall_id is too small or too big.\n");
        return NULL;
    }

    return wascall_table[wascall_id];
}

int32_t wascall_dispatch(uint32_t wascall_id, int32_t *args, int32_t *rets) {
    wascall_handler_t handler = wascall_get_handler(wascall_id);
    if (!handler) {
        printf("[Failed] cannot get wascall handler.\n");
        return -1;
    }

    return handler(args, rets);
}

void wascall_register(uint32_t wascall_id, wascall_handler_t handler) {
    if (wascall_id >= MAX_CALLS) {
        printf("[Failed] wascall_id out of table.\n");
        return;
    }

    if (wascall_id > 0) {
        printf("[Failed] wascall_id: %u already exsist!\n", wascall_id);
        return;
    }

    wascall_table[wascall_id] = handler;
}




// 초기화용 함수
extern wascall_handler_t get_default_handler(uint32_t wascall_id);

__attribute__((constructor))
static void wascall_init_table() {
    for (uint32_t i = 0; i < MAX_CALLS; ++i) {
        wascall_table[i] = get_default_handler(i);
    }
}