#pragma once

void print_help(char* _[], int);

typedef struct {
    char* name;
    char shorten_name;
    void (*func)(char* params[], int params_len);
} flag_t;

typedef struct ll_flag ll_flag; // forward declaration

typedef struct ll_flag { // linked list
    flag_t *data;
    ll_flag *next;
} ll_flag;

void parse_flags(int argc, char* argv[]);