#ifndef HAIL_IO_H
#define HAIL_IO_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

uint8_t* load_file_to_memory(const char *path, uint32_t *out_size);


#endif // HAIL_IO_H