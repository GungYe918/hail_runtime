#include <hail/sys/wascall/wascall.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX_CALLS WASCALL_MAX
#define MAX_ARGS 8


static wascall_entry_t wascall_table[MAX_CALLS] = { 0 };

int wascall_table_init(void) {
    extern const wascall_entry_t *get_default_handler_table(void);
    const wascall_entry_t *defaults = get_default_handler_table();
    if (!defaults) {
        printf("[Wascall] Default handler table missing. table init failed.\n");
        return -1;
    }

    memcpy(wascall_table, defaults, sizeof(wascall_table));
    return 0;
}


wascall_handler_t wascall_get_handler(uint32_t wascall_id) {
    if (wascall_id >= MAX_CALLS) {
        printf("[Wascall] Invalid ID %u\n", wascall_id);
        return NULL;
    }
    return wascall_table[wascall_id].handler;
}

int wascall_register(uint32_t wascall_id, wascall_handler_t handler) {
    if (wascall_id >= MAX_CALLS || handler == NULL) {
        printf("[Wascall] ID %u out of range. failed.\n", wascall_id);
        return -1;
    }
    if (wascall_table[wascall_id].handler != NULL) {
        printf("[Wascall] ID %u already registered\n", wascall_id);
        return -2;
    }

    wascall_table[wascall_id].handler = handler;
    wascall_table[wascall_id].argc = MAX_ARGS;
    return 0;
}

int32_t wascall(uint32_t wascall_id, ...) {
    if (wascall_id >= MAX_CALLS) {
        printf("[Wascall] Invalid ID %u\n", wascall_id);
        return -1;
    }

    wascall_entry_t entry = wascall_table[wascall_id];
    if (!entry.handler) {
        printf("[Wascall] No handler for ID %u\n", wascall_id);
        return -2;
    }

    uint8_t argc = entry.argc;
    if (argc > MAX_ARGS) {
        printf("[Wascall] Argument count too large (%u)\n", argc);
        return -3;
    }

    int32_t args[MAX_ARGS] = { 0 };
    int32_t *rets = NULL;

    va_list va;
    va_start(va, wascall_id);

    for (uint8_t i = 0; i < argc; ++i) {
        args[i] = va_arg(va, int32_t);
    }

    // 마지막 인자 -> rets 포인터
    void *last = va_arg(va, void *);
    va_end(va);

    if (((uintptr_t)last % sizeof(void *)) != 0) {
        printf("[Wascall] Last var argument is not a valid pointer alignment\n");
        return -4;
    }

    rets = (uint32_t *)last;

    return entry.handler(args, rets);
}