#include <stdio.h>
#include "token.h"

TokenType int_type_check(const char* str)
{
    unsigned long long val = strtoull(str, NULL, 10);

    if (val <= 255ULL)
        return TOKEN_INT1;
    else if (val <= 65535ULL)
        return TOKEN_INT2;
    else if (val <= 4294967295ULL)
        return TOKEN_INT4;
    else
        return TOKEN_INT8;
}

bool is_binary_op(const TokenType type)
{
    if(type >= TOKEN_ADD && type <= TOKEN_DIV)
        return true;

    return false;
}

bool is_number_tokenType(const TokenType type)
{
    if(type >= TOKEN_INT1 && type <= TOKEN_FLOAT16)
        return true;

    return false;
}