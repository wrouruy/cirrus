#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char* name;
    void (*func)(void);
} flag_t;

char** get_signs(char* flag, int* counter)
{ 
    *counter = 0;
    char** res = malloc(sizeof(char*) * 16);
    for(int i = 1; i < global_argc; i++) {
        if(strcmp(global_argv[i], flag) == 0)
            continue;
        res[*counter] = global_argv[i];
        (*counter)++;
    }
    return res;
}

void print_help()
{
    puts("<file.crs> -S : compile cirrus file to assembler\n"
         "    --version : print compiler version\n"
         "       --repo : open compiler repository (on github)\n"
         "       --help : print this help message");
}

void print_version()
{
    char* path = get_path("settings.conf");
    char* version = config_reader(path, "version");
    printf("%s\n", version);
    free(version);
}

void open_repo()
{
    open_url("https://github.com/wrouruy/cirrus");
}

void build_asm()
{
    char* file_src;
    int count_flags;
    char** arr_sings = get_signs("-S", &count_flags);

    // check input data
    if(count_flags > 0)
        file_src = arr_sings[0];
    else ThrowError("Error", "no input files");

    if(!file_exists(file_src))
        ThrowError("Error", "the \033[1m%s\033[0m file is not exist", file_src);
    else if(file_type(file_src) != 1) ThrowError("Error", "input data is not a file");

    char* fsrc = fvalue(file_src); // get file data & record to buffer

    // Lexer
    size_t tokens_count; // create tokens count
    Token* tokens = Lexer(fsrc, &tokens_count); // create list of tokens

    free(fsrc); // rm buffer

    // Parser
    size_t parser_count = 0;
    AST* ast = Parser(tokens, tokens_count, &parser_count);

    printAST(ast, 1);

    free_lexer(tokens, tokens_count); // rm tokens

    free_ast(ast); // rm ast
}