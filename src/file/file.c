#include <stdlib.h>
#include <stdio.h>

char* file_read(
    const char* filename,
    long* size
) {
    FILE* fsrc = fopen(filename, "rb");
    if (!fsrc) return NULL;
    fseek(fsrc, 0, SEEK_END);
    *size = ftell(fsrc);
    rewind(fsrc);

    char* buffer = malloc(*size + 1);
    fread(buffer, 1, *size, fsrc);
    buffer[*size] = '\0';
    fclose(fsrc);

    return buffer;
}
