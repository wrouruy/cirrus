#include <stdio.h>
#include <stdlib.h>
#include "../../lexer/lexer.h"
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

    size_t token_size;
    lex_token_t* token = tokenize(fval, fsize, &token_size);

    free(fval);

    for (size_t i = 0; i < token_size; i++) {
        printf("%ld : val: '%s' ; type: %d\n", i, token[i].value, token[i].type);
    }

    lex_free(token, token_size);
}