#pragma once
#include <stddef.h>
#include "flag.h"

flag_t flags[] = {
    { "--help", 'h', print_help },
    { "--build", 'b', build },
};
size_t flags_len = sizeof(flags) / sizeof(flags[0]);