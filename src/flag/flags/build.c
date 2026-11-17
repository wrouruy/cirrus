#include <stdio.h>
#include <stdlib.h>
#include "../../lexer/lexer.h"
#include "../../ast/ast.h"
#include "../../error/error.h"
#include "../../file/file.h"

void build (char* params[], int params_len) {
    if (params_len < 1)
        raise_error("no input file");

    const char *filename = params[0];

    long fsize;
    char* fval = file_read(filename, &fsize);

    if (!fval)
        raise_error("file \"%s\" does not exist", filename);

    size_t token_len;
    lex_token_t* token = tokenize(filename, fval, fsize, &token_len);

    free(fval);

    size_t ast_len = 0;
    ast_t *ast = parser(token, token_len, &ast_len);

    lex_free(token, token_len);

    ast_free(ast);
}