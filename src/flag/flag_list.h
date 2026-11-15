#pragma once
#include <stddef.h>
#include "flag.h"

flag_t flags[] = {
    { "--help", 'h', print_help },
};
size_t flags_len = sizeof(flags) / sizeof(flags[0]);