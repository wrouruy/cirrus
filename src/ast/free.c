#include <stdlib.h>
#include "ast.h"

void ast_free(ast_t* ast) {
    if (!ast) return;
    switch (ast->type)
    {
        case ast_binary_op:
            free(ast->binary.op);
            ast_free(ast->binary.left);
            ast_free(ast->binary.right);
            break;
        case ast_func_def:
            free(ast->func_def.name);
            for(size_t i = 0; i < ast->func_def.arg_count; i++)
                ast_free(ast->func_def.args[i]);
            if (ast->func_def.body)
                ast_free(ast->func_def.body);
            break;
        case ast_func_call:
            for(size_t i = 0; i < ast->func_call.arg_count; i++)
                ast_free(ast->func_call.args[i]);
            break;
        default: break;
    }
    free(ast);
}