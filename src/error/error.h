#pragma once

#include <stddef.h>

void raise_error(char* err, ...);
void raise_err_code(const char* file, const char* src, size_t index, const char* err, ...);
