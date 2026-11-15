#include <stddef.h>
#include <stdlib.h>
#include "lexer.h"

void lex_free(lex_token_t* t, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(t[i].value);
    }
    free(t);
}