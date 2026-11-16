#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define TAB_WIDTH 4

typedef struct {
    size_t line;
    size_t line_start;
    size_t line_end;
    size_t col;
} source_pos_t;

static source_pos_t source_locate(const char* src, size_t index) {
    source_pos_t pos = { 1, 0, 0, 1 };
    if (!src) return pos;

    for (size_t i = 0; i < index && src[i] != '\0'; i++) {
        if (src[i] == '\n') {
            pos.line++;
            pos.line_start = i + 1;
        }
    }

    pos.line_end = pos.line_start;
    while (src[pos.line_end] != '\0' && src[pos.line_end] != '\n')
        pos.line_end++;

    // Do not show the carriage return of CRLF files.
    if (pos.line_end > pos.line_start && src[pos.line_end - 1] == '\r')
        pos.line_end--;

    pos.col = index - pos.line_start + 1;
    if (index > pos.line_end)
        pos.col = pos.line_end - pos.line_start + 1;

    return pos;
}

static size_t display_width(const char* src, size_t start, size_t end) {
    size_t width = 0;
    for (size_t i = start; i < end; i++) {
        if (src[i] == '\t')
            width += TAB_WIDTH - (width % TAB_WIDTH);
        else
            width++;
    }
    return width;
}

static void print_source_snippet(const char* src, source_pos_t pos) {
    if (!src) return;

    int gutter = snprintf(NULL, 0, "%zu", pos.line);
    if (gutter < 0) gutter = 0;

    fprintf(stderr, " %*zu | ", gutter, pos.line);

    size_t width = 0;
    for (size_t i = pos.line_start; i < pos.line_end; i++) {
        if (src[i] == '\t') {
            size_t spaces = TAB_WIDTH - (width % TAB_WIDTH);
            for (size_t j = 0; j < spaces; j++) fputc(' ', stderr);
            width += spaces;
        } else {
            fputc((unsigned char)src[i], stderr);
            width++;
        }
    }
    fputc('\n', stderr);

    size_t caret = display_width(src, pos.line_start, pos.line_start + (pos.col - 1));

    fprintf(stderr, " %*s | ", gutter, "");
    for (size_t i = 0; i < caret; i++) fputc(' ', stderr);
    fprintf(stderr, "\033[1;31m^\033[0m\n");
}

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

void raise_err_code(const char* file, const char* src, size_t index, const char* err, ...) {
    va_list args;
    va_start(args, err);

    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, err, args_copy);
    va_end(args_copy);

    char* buffer = NULL;
    if (needed >= 0) {
        buffer = malloc((size_t)needed + 1);
        if (buffer)
            vsnprintf(buffer, (size_t)needed + 1, err, args);
    }
    va_end(args);

    const char* message = buffer ? buffer : err;
    source_pos_t pos = source_locate(src, index);

    if (file && *file)
        fprintf(stderr, "%s:%zu:%zu: \033[1;31merr:\033[0m %s\n",
                file, pos.line, pos.col, message);
    else
        fprintf(stderr, "%zu:%zu: \033[1;31merr:\033[0m %s\n",
                pos.line, pos.col, message);

    print_source_snippet(src, pos);

    free(buffer);
    exit(1);
}
