#include <stdio.h>
#include <hail/runtime/runtime.h>

int main(void) {
    if (runtime_init() != 0) {
        printf("[Failed] init runtime!\n");
        return -1;
    }

    printf("[Success] runtime has inited!\n");
    return 0;
}