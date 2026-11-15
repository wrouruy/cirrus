#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

static lex_token_t make_token(lex_type_t type, const char* start, int len) {
    lex_token_t t;
    t.type = type;
    t.value = malloc(len + 1);
    strncpy(t.value, start, len);
    t.value[len] = '\0';

    return t;
}

lex_token_t* tokenize(const char* input, size_t size, size_t* count) {
    lex_token_t* res = malloc(sizeof(lex_token_t) * size);
    *count = 0;

    for (size_t i = 0; input[i] != '\0';) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isdigit(input[i])) {
            size_t start = i;
            while (isdigit(input[i])) i++;
            res[*count] = make_token(lexer_int, &input[start], i - start);
            (*count)++;
        }
        i++;
    }

    res[*count] = make_token(lexer_eof, "", 0);
    (*count)++;

    return res;
}