#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

char** global_argv;
int global_argc;

#include "utils.h"
#include "conf-reader.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "Translate/asm.h"
#include "flags.h"

int main(int argc, char* argv[])
{
    global_argv = argv;
    global_argc = argc;

    flag_t flags[] = {
        { "--help", print_help    },
        { "-h",     print_help    },
        { "--version", print_version },
        { "-v",        print_version },
        { "--repo", open_repo     },
        { "-S",     build_asm     }
    };

    for(int i = 0; i < sizeof(flags) / sizeof(flag_t); i++)
        if(include_str(flags[i].name, argv, argc)){
            flags[i].func();
            return 0;
        }

    return 0;
}