#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


void raise_error(char* err, ...) {
    va_list args;
    char* buffer = malloc(512);
    size_t buffer_size = 512;

    va_start(args, err);
    vsnprintf(buffer, buffer_size, err, args);
    va_end(args);

    printf("\033[1;31merr:\033[0m %s\n", buffer);
    exit(1);
}