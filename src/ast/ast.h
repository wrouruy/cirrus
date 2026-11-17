#pragma once
#include "../lexer/lexer.h"

typedef enum {
    ast_number,
    ast_binary_op,
    ast_func_def,
    ast_func_call,
    ast_ident
} ast_type;

typedef struct ast_t ast_t;

typedef struct {
    char* name;
    lex_type_t func_type;
    ast_t** args;
    size_t arg_count;
    ast_t* body;
} ast_func_def_t;

typedef struct {
    char name[64];
    ast_t** args;
    size_t arg_count;
} ast_func_call_t;

typedef struct {
    char value[64];
} ast_number_t;

typedef struct {
    char* op;
    ast_t* left;
    ast_t* right;
} ast_binary_op_t;

struct ast_t {
    ast_type type;
    union {
        ast_number_t number;
        ast_binary_op_t binary;
        ast_func_def_t func_def;
        ast_func_call_t func_call;
    };
};

ast_t* parser(lex_token_t* t, size_t t_len, size_t* count);
void ast_free(ast_t* ast);