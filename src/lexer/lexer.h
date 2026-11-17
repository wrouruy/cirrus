#pragma once

#include <stddef.h>

typedef enum {
    lexer_ident,
    lexer_keyword,

    lexer_add,
    lexer_sub,
    lexer_mul,
    lexer_div,

    lexer_equal,
    lexer_lparen,
    lexer_rparen,

    lexer_num,
    lexer_str,

    lexer_eof
} lex_type_t;

typedef enum {
    lexer_kw_none,
    lexer_kw_import,
    lexer_kw_as,
    lexer_kw_if,
    lexer_kw_else,

    lexer_kw_while,
    lexer_kw_for,

    lexer_kw_const,
    lexer_kw_int,
    lexer_kw_char,
    lexer_kw_void,
    
    lexer_kw_return,

    lexer_kw_true,
    lexer_kw_false,
} lex_kw_t;

typedef struct {
    char* value;
    lex_type_t type;
    lex_kw_t kw;
} lex_token_t;

lex_token_t* tokenize(const char* file, const char* input, size_t size, size_t* count);
void lex_free(lex_token_t* t, size_t size);