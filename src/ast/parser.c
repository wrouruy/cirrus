#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "../lexer/lexer.h"

static ast_t* mk_number_ast(const char* value)
{
    ast_t* node = malloc(sizeof(ast_t));
    node->type = ast_number;
    strcpy(node->number.value, value);
    return node;
}

static ast_t* mk_binary_op_ast(const char* op, ast_t* left, ast_t* right)
{
    ast_t* node = malloc(sizeof(ast_t));
    node->type = ast_binary_op;
    node->binary.op = malloc(5);
    strcpy(node->binary.op, op);
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

void printAST(ast_t* ast, int tabtime)
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
        case ast_number:
            printf("%stype: \"ast_number\"\n%snumber: %s\n", tabs, tabs, ast->number.value);
            break;
        case ast_binary_op:
            printf("%stype: \"binary_op\"\n%soperation: \"%s\"\n%sleft: ", tabs, tabs, ast->binary.op, tabs);
            printAST(ast->binary.left, tabtime+1);
            printf("%sright: ", tabs);
            printAST(ast->binary.right, tabtime+1);
            break;
        case ast_func_def:
            printf("%stype: \"func_def\"\n%sname: \"%s\"\n%sarg_count: %ld\n%stype_func: %d\n%sbody: ", tabs, tabs, ast->func_def.name, tabs, ast->func_def.arg_count, tabs, ast->func_def.func_type, tabs);
            printAST(ast->func_def.body, tabtime+1);
            break;
        case ast_func_call:
            printf("%stype: \"func_call\"\n%sname: \"%s\"\n%sarg_count: %ld\n%sargs: ", tabs, tabs, ast->func_call.name, tabs, ast->func_call.arg_count, tabs);
            for(size_t i = 0; i < ast->func_call.arg_count; i++)
                printAST(ast->func_call.args[i], tabtime+1);
            break;
        default: break;
    }

    printf("%s\b\b\b", tabs);
    puts("}");
}

ast_t* parse_factor(lex_token_t* tokens, size_t* i)
{
    ast_t* node = mk_number_ast(tokens[*i].value);
    (*i)++;
    return node;
}

ast_t* parse_term(lex_token_t* tokens, size_t* i)
{
    ast_t* left = parse_factor(tokens, i);

    while (tokens[*i].type == lexer_mul ||
           tokens[*i].type == lexer_div) {
        lex_token_t op = tokens[*i];
        (*i)++;

        ast_t* right = parse_factor(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }

    return left;
}

ast_t* parse_operation(lex_token_t* tokens, size_t* i)
{
    ast_t* left = parse_term(tokens, i);

    while (tokens[*i].type == lexer_add ||
           tokens[*i].type == lexer_sub) {
        lex_token_t op = tokens[*i];
        (*i)++;

        ast_t* right = parse_term(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }
    return left;
}

ast_t* parser(lex_token_t* t, size_t t_len, size_t* count) {
    if (!t || !count) return NULL;
    *count = 0;

    ast_t* res = calloc(1, sizeof(ast_t));
    if (!res) return NULL;

    res->type = ast_func_def;

    size_t i = 0;
    while (i < t_len && t[i].type != lexer_eof) {
        if (t[i].type == lexer_num) {
            res->func_def.body = parse_operation(t, &i);
            *count = 1;
        } else {
            i++;
        }
    }

    printAST(res, 0);

    return res;
}