#pragma once

typedef enum {
    lexer_ident,

    lexer_add,
    lexer_sub,
    lexer_mul,
    lexer_div,

    lexer_equal,
    lexer_lparen,
    lexer_rparen,

    lexer_int,
    lexer_str,

    lexer_eof
} lex_type_t;

typedef struct {
    char* value;
    lex_type_t type;
} lex_token_t;

lex_token_t* tokenize(const char* input, size_t size, size_t* count);
void lex_free(lex_token_t* t, size_t size);