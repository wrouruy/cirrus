#include "token.h"
#include "utils.h"

Token make_token(TokenType type, const char* start, int length)
{
    Token t;
    t.type = type;
    t.value = malloc(length + 1);
    strncpy(t.value, start, length);
    t.value[length] = '\0';
    return t;
}

Token* tokenize(const char* input, size_t* token_count)
{
    Token* tokens = malloc(1024 * sizeof(Token));
    int count = 0;

    for (size_t i = 0; input[i] != '\0'; ) {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if(input[i] == '/' && input[i + 1] == '/')
            while(true){
                if(input[i] == '\n' || input[i] == '\0') break;
                i++;
            }

        if (isalpha(input[i]) || input[i] == '_') { // word
            int start = i;
            while (isalnum(input[i]) || input[i] == '_') i++;
            tokens[count++] = make_token(TOKEN_IDENT, &input[start], i - start);
            continue;
        }

        if (isdigit(input[i])) { // int
            int start = i;
            while (isdigit(input[i])) i++;
            tokens[count++] = make_token(int_type_check(&input[start]), &input[start], i - start);
            continue;
        }
        /*
        if (input[i] == '"') { // string
            int start = ++i;
            while (input[i] != '"' && input[i] != '\0') i++;
            tokens[count++] = make_token(TOKEN_STRING, &input[start], i - start);
            i++;
            continue;
        } */

        if (input[i] == '=') {
            tokens[count++] = make_token(TOKEN_EQUAL, "=", 1);
            i++;
            continue;
        }
        if (input[i] == '+') {
            tokens[count++] = make_token(TOKEN_PLUS, "+", 1);
            i++;
            continue;
        }
        if (input[i] == '*') {
            tokens[count++] = make_token(TOKEN_MULT, "*", 1);
            i++;
            continue;
        }
        if (input[i] == '-') {
            tokens[count++] = make_token(TOKEN_MINUS, "-", 1);
            i++;
            continue;
        }
        if (input[i] == '/') {
            tokens[count++] = make_token(TOKEN_DIV, "/", 1);
            i++;
            continue;
        }
        if (input[i] == '(') {
            tokens[count++] = make_token(TOKEN_LPAREN, "(", 1);
            i++;
            continue;
        }
        if (input[i] == ')') {
            tokens[count++] = make_token(TOKEN_RPAREN, ")", 1);
            i++;
            continue;
        }

        if (input[i] == ';') {
            tokens[count++] = make_token(TOKEN_SEMICOLON, ";", 1);
            i++;
            continue;
        }

        i++;
    }

    tokens[count++] = make_token(TOKEN_EOF, "", 0);
    *token_count = count;
    return tokens;
}
/*
typedef struct
{
    size_t count;
    Token* value;
} semicolon;

semicolon* semicolonize(Token* tokens, size_t tokenCount, size_t* count)
{
    if (tokenCount <= 1)
        exit(1);

    semicolon* res = malloc(sizeof(semicolon) * 512);
    size_t semi_count = 0;
    size_t iteration = 0;

    res[semi_count].value = malloc(sizeof(Token) * 16);

    for (size_t i = 0; i < tokenCount; i++) {
        if (tokens[i].type == TOKEN_SEMICOLON) {
            res[semi_count].count = iteration;
            semi_count++;
            iteration = 0;
            res[semi_count].value = malloc(sizeof(Token) * 16);
            continue;
        }
        res[semi_count].value[iteration] = tokens[i];
        iteration++;
    }

    res[semi_count].count = iteration;
    *count = semi_count + 1;

    return res;
}
*/