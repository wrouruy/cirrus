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

    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
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

typedef struct {
    TokenType type;
    char* value;
} typization_t;

typization_t typization[] = {
    { TOKEN_INT1, "int1" },
    { TOKEN_INT2, "int2" },
    { TOKEN_INT4, "int4" },
    { TOKEN_INT8, "int8" },

    { TOKEN_FLOAT4,  "float4"  },
    { TOKEN_FLOAT8,  "float8"  },
    { TOKEN_FLOAT16, "float16" },

    { TOKEN_VOID, "void" }
};

bool include_typization(char* type_str, TokenType* type_share) { // linear search algorithm
    for(int i = 0; i < sizeof(typization) / sizeof(typization_t); i++)
        if(strcmp(typization[i].value, type_str) == 0){
            *type_share = typization[i].type;
            return true;
        }

    return false;
}