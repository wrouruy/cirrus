#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "../error/error.h"
#include "lexer.h"
#include "keywords.h"

static void untermined_str_err(const char* file, const char* input, size_t index);

static lex_token_t make_token(lex_type_t type, const char* start, size_t len) {
    lex_token_t t;
    t.type = type;
    t.kw = lexer_kw_none;
    t.value = malloc(len + 1);
    memcpy(t.value, start, len);
    t.value[len] = '\0';

    return t;
}

static const char opers[] = { '+', '-', '*', '/', '=', '(', ')' };
static const char types[] = { lexer_add, lexer_sub, lexer_mul, lexer_div, lexer_equal, lexer_lparen, lexer_rparen };

static lex_kw_t keyword_lookup(const char* start, size_t len) {
    for (size_t i = 0; i < keywords_len; i++) {
        if (strlen(keywords[i].word) == len &&
            memcmp(keywords[i].word, start, len) == 0)
            return keywords[i].kw;
    }
    return lexer_kw_none;
}

static bool tokenize_operation (
    char* c,
    lex_token_t* t,
    size_t* count
){
    for (size_t i = 0; i < sizeof(opers) / sizeof(opers[0]); i++) {
        if (*c == opers[i]) {
            t[*count] = make_token(types[i], c, 1);
            (*count)++;
            return true;
        }
    }
    return false;
}

lex_token_t* tokenize(const char* file, const char* input, size_t size, size_t* count) {
    lex_token_t* res = malloc(sizeof(lex_token_t) * (size + 1));
    *count = 0;

    for (size_t i = 0; i < size && input[i] != '\0';) {
        char c = input[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (c == '#') {
            while (i < size && input[i] != '\n') i++;
            continue;
        }

        // ident
        if (isalpha((unsigned char)c) || c == '_') {
            size_t start = i;
            while (i < size && (isalnum((unsigned char)input[i]) || input[i] == '_')) i++;
            size_t len = i - start;

            lex_kw_t kw = keyword_lookup(&input[start], len);
            if (kw != lexer_kw_none) {
                res[*count] = make_token(lexer_keyword, &input[start], len);
                res[*count].kw = kw;
            } else {
                res[*count] = make_token(lexer_ident, &input[start], len);
            }
            (*count)++;
            continue;
        }

        // operations
        if (tokenize_operation(&c, res, count)) {
            i++;
            continue;
        }

        // int
        if (isdigit(c)) {
            size_t start = i;
            while (i < size && isdigit(input[i])) i++;
            res[*count] = make_token(lexer_num, &input[start], i - start);
            (*count)++;
            continue;
        }

        // string
        if (c == '"') {
            size_t start = ++i;
            while (i < size && input[i] != '"') {
                if (input[i] == '\n' || input[i] == '\0')
                    untermined_str_err(file, input, i);
                i++;
            }
            if (i >= size)
                untermined_str_err(file, input, i);
            res[*count] = make_token(lexer_str, &input[start], i - start);
            (*count)++;
            i++;
            continue;
        }

        i++;
    }

    res[*count] = make_token(lexer_eof, "", 0);
    (*count)++;

    return res;
}


/* error messages */

static void untermined_str_err(const char* file, const char* input, size_t index) {
    raise_err_code(file, input, index, "unterminated string literal");
}