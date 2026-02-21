#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST_t.h"

// create number
AST* mk_number_ast(const char* value)
{
    AST* node = malloc(sizeof(AST));
    node->type = AST_NUMBER;
    strcpy(node->number.value, value);
    return node;
}

// create binary operation
AST* mk_binary_op_ast(const char* op, AST* left, AST* right)
{
    AST* node = malloc(sizeof(AST));
    node->type = AST_BINARY_OP;
    node->binary.op = malloc(5);
    strcpy(node->binary.op, op);
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

// debug function
void printAST(AST* ast, int tabtime)
{
    if(ast == NULL){
        printf("{}\n");
        return;
    }
    char tabs[300] = "\0";
    for(int i = 0; i < tabtime; i++)
        strcat(tabs, "   ");
    puts("{");

    switch (ast->type)
    {
        case AST_NUMBER:
            printf("%stype: \"AST_NUMBER\"\n%snumber: %s\n", tabs, tabs, ast->number.value);
            break;
        case AST_BINARY_OP:
            printf("%stype: \"BINARY_OP\"\n%soperation: \"%s\"\n%sleft: ", tabs, tabs, ast->binary.op, tabs);
            printAST(ast->binary.left, tabtime+1);
            printf("%sright: ", tabs);
            printAST(ast->binary.right, tabtime+1);
            break;
        case AST_FUNCTION_DEF:
            printf("%stype: \"FUNCTION_DEF\"\n%sname: \"%s\"\n%sarg_count: %d\n%stype_func: %d\n%sbody: ", tabs, tabs, ast->func_def.name, tabs, ast->func_def.arg_count, tabs, ast->func_def.func_type, tabs);
            printAST(ast->func_def.body, tabtime+1);
            break;
        case AST_FUNCTION_CALL:
            printf("%stype: \"FUNCTION_CALL\"\n%sname: \"%s\"\n%sarg_count: %d\n%sargs: ", tabs, tabs, ast->func_call.name, tabs, ast->func_call.arg_count, tabs);
            for(int i = 0; i < ast->func_call.arg_count; i++)
                printAST(ast->func_call.args[i], tabtime+1);
            break;
    }

    printf("%s\b\b\b", tabs);
    puts("}");
}

AST* parse_factor(Token* tokens, size_t* i)
{
    AST* node = mk_number_ast(tokens[*i].value);
    (*i)++;
    return node;
}

AST* parse_term(Token* tokens, size_t* i)
{
    AST* left = parse_factor(tokens, i);

    while (tokens[*i].type == TOKEN_MUL ||
           tokens[*i].type == TOKEN_DIV) {
        Token op = tokens[*i];
        (*i)++;

        AST* right = parse_factor(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }

    return left;
}

AST* parse_operation(Token* tokens, size_t* i)
{
    AST* left = parse_term(tokens, i);

    while (tokens[*i].type == TOKEN_ADD ||
           tokens[*i].type == TOKEN_SUB) {
        Token op = tokens[*i];
        (*i)++;

        AST* right = parse_term(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }
    return left;
}

AST* Parser(Token* tokens, size_t token_count, size_t* i) {
    AST* res = calloc(1, sizeof(AST));
    res->type = AST_FUNCTION_DEF;

    TokenType ttoken;

    while(tokens[*i].type != TOKEN_EOF) {
        if(is_number_tokenType(tokens[*i].type)) {
            res->func_def.body = parse_operation(tokens, i);
        } //else if(include_typization(tokens[*i].value, &ttoken)){ printf("%d\n", ttoken); (*i)++; }
        else (*i)++;
    }

    return res;
}

void free_ast(AST* ast) // recursive free ast
{
    if (!ast) return;
    switch (ast->type) // тут щось не так
    {
        case AST_BINARY_OP:
            free(ast->binary.op);
            free_ast(ast->binary.left);
            free_ast(ast->binary.right);
            break;
        case AST_FUNCTION_DEF:
            free(ast->func_def.name);
            for(size_t i = 0; i < ast->func_def.arg_count; i++)
                free_ast(ast->func_def.args[i]);
            if (ast->func_def.body)
                free_ast(ast->func_def.body);
            break;
        case AST_FUNCTION_CALL:
            for(size_t i = 0; i < ast->func_call.arg_count; i++)
                free_ast(ast->func_call.args[i]);
            break;
    }
    free(ast);
}