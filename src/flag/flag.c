#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "flag.h"
#include "../error/error.h"
#include "flag_list.h"

static flag_t *flag_by_fullname (char* flag) {
    for (int i = 0; i < flags_len; i++) {
        if (strcmp(flags[i].name, flag) == 0)
            return &flags[i];
    }
    return NULL;
}

static flag_t* flag_by_shortname(char flag) {
    for (int i = 0; i < flags_len; i++) {
        if (flags[i].shorten_name == flag)
            return &flags[i];
    }
    return NULL;
}

void parse_flags(int argc, char* argv[]) {
    char *params[argc] = {};
    int params_len = 0;

    ll_flag *f = malloc(sizeof(ll_flag));
    ll_flag *fnext = f;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') { // if flag start with "--"
                fnext->data = flag_by_fullname(argv[i]);
                
                if (fnext->data == NULL)
                    raise_error("unknown flag \"%s\"", argv[i]);
                fnext->next = malloc(sizeof(ll_flag));
                
                fnext = fnext->next;
            } else { // if flag is shorten
                char *p = argv[i] + 1;
                while(*p != '\0') {
                    fnext->data = flag_by_shortname(*p);
                    if (fnext->data == NULL)
                        raise_error("unknown flag \"-%c\"", *p);

                    fnext->next = malloc(sizeof(ll_flag));
                    fnext = fnext->next;
                    p++;
                }
            }

        } else {
            params[params_len] = argv[i];
            params_len++;
        }
    }

    if (!f->data && params_len > 0)
        raise_error("unexpected parameters without any flags");

    while(f->next != NULL) {
        ll_flag* fnext = f->next;
        f->data->func(params, params_len);

        free(f);
        f = fnext;
    }
}