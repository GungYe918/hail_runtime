#ifndef HAIL_STUB_H
#define HAIL_STUB_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// 미구현 함수 표시
#define STUB() \
    (printf("[Info] Func \'%s\' not implemented\n", __func__), -1)


#ifdef __cplusplus
}
#endif


#endif