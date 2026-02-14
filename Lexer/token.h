#pragma once
typedef enum {
    TOKEN_IDENT,

    TOKEN_INT1,
    TOKEN_INT2,
    TOKEN_INT4,
    TOKEN_INT8,

    TOKEN_FLOAT4,
    TOKEN_FLOAT8,
    TOKEN_FLOAT16,

    TOKEN_VOID,
    TOKEN_VAR,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_EQUAL,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct
{
    TokenType type;
    char* value;
} Token;