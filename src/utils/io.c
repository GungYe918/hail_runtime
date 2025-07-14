#include <hail/utils/io.h>


uint8_t* load_file_to_memory(const char *path, uint32_t *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        printf("[Failed] failed to open file.\n");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t *buf = malloc(size);
    if (!buf) {
        fclose(f);
        printf("[Failed] malloc failed.\n");
        return NULL;
    }

    fread(buf, 1, size, f);
    fclose(f);

    *out_size = (uint32_t)size;
    return buf;
}