#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST_t.h"

// create number
AST* mk_number_ast(const char* value) {
    AST* node = malloc(sizeof(AST));
    node->type = AST_NUMBER;
    strcpy(node->valueStr, value);
    node->left = node->right = NULL;
    return node;
}

// create binary operation
AST* mk_binary_op_ast(const char* op, AST* left, AST* right) {
    AST* node = malloc(sizeof(AST));
    node->type = AST_BINARY_OP;
    strcpy(node->valueStr, op);
    node->left = left;
    node->right = right;
    return node;
}

// print AST as JSON
void printAST(AST node, int tabtime) {
    puts("{");
    char tabstr[128] = "\0";
    for(int i = 0; i < tabtime; i++)
        strcat(tabstr, "   ");
    printf("%stype: \"%s\"\n%svalue: \"%s\"\n", tabstr, node.type == AST_NUMBER ? "AST_NUMBER" : "AST_BINARY_OP", tabstr, node.valueStr);
    
    if(node.type == AST_BINARY_OP){
        printf("%sleft: ", tabstr);
        printAST(*node.left, tabtime+1);
        printf("%sright: ", tabstr);
        printAST(*node.right, tabtime+1);
    }
    for(int i = 0; i < tabtime - 1; i++)
        printf("%s", tabtime == 0 ? "": "   ");
    puts("}");
}

AST* parse_factor(Token* tokens, size_t* i) {
    AST* node = mk_number_ast(tokens[*i].value);
    (*i)++;
    return node;
}

AST* parse_term(Token* tokens, size_t* i) {
    AST* left = parse_factor(tokens, i);

    while (tokens[*i].type == TOKEN_MULT ||
           tokens[*i].type == TOKEN_DIV) {
        Token op = tokens[*i];
        (*i)++;

        AST* right = parse_factor(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }

    return left;
}

AST* Parser(Token* tokens, size_t token_count, size_t* i) {
    AST* left = parse_term(tokens, i);

    while (tokens[*i].type == TOKEN_PLUS ||
           tokens[*i].type == TOKEN_MINUS) {
        Token op = tokens[*i];
        (*i)++;

        AST* right = parse_term(tokens, i);
        left = mk_binary_op_ast(op.value, left, right);
    }

    return left;
}
