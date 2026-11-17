#include "lexer.h"

typedef struct {
    const char* word;
    lex_kw_t kw;
} keyword_t;

const keyword_t keywords[] = {
    { "import", lexer_kw_import },
    { "as",     lexer_kw_as     },
    { "if",     lexer_kw_if     },
    { "else",   lexer_kw_else   },
    { "while",  lexer_kw_while  },
    { "for",    lexer_kw_for    },

    { "const",  lexer_kw_const  },
    { "int",    lexer_kw_int    },
    { "char",   lexer_kw_char   },
    { "void",   lexer_kw_void   },
    { "return", lexer_kw_return },

    { "True",   lexer_kw_true   },
    { "False",  lexer_kw_false  },
};
const size_t keywords_len = sizeof(keywords) / sizeof(keywords[0]);