#include <stdio.h>
#include <stdlib.h>
#include <hail/runtime/runtime.h>
#include <hail/loader/wasm_loader.h>
#include <hail/utils/io.h>
#include <hail/sys/api/native_api.h>


#include <hail/sys/wascall/wascall.h>
#include <string.h>

int main(void) {
    if (runtime_init() != 0) {
        printf("[Failed] init runtime!\n");
        return -1;
    } else {
        printf("[Success] runtime has inited!\n");
    }

    uint32_t wasm_size;
    uint8_t *wasm_buf = load_file_to_memory("../tests/add.wasm", &wasm_size);

    if (!wasm_buf) {
        printf("[Failed] failed to load wasm file.\n");
        return -2;
    }

    char error_buf[256];
    wasm_module_t module = hail_load_module(wasm_buf, wasm_size, error_buf, sizeof(error_buf));
    if (!module) {
        printf("[Failed] module load failed: %s\n", error_buf);
        return -3;
    }

    wasm_module_inst_t inst = hail_create_instance(module, STACK_SIZE, HAIL_RUNTIME_HEAP_SIZE, error_buf, sizeof(error_buf));
    if (!inst) {
        printf("[Failed] create instance failed: %s\n", error_buf);
        return -4;
    }

    printf("[Success] WASM module loaded and instance created!\n");

    wasm_val_t args[2] = {
        {   .kind = WASM_I32, .of.i32 = 10  },
        {   .kind = WASM_I32, .of.i32 = 100  },
    };
    wasm_val_t result = { .kind = WASM_I32 };


    if (hail_call_function(inst, "add", args, 2, &result, 1, error_buf, sizeof(error_buf)) == 0) {
        printf("add(10, 100) = %d\n", result.of.i32);
    } else {
        printf("%s\n", error_buf);
    }

    hail_destroy_instance(inst);
    hail_unload_module(module);
    free(wasm_buf);
    return 0;
}