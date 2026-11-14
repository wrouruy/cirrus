#pragma once

void print_help(char* _[], int);

typedef struct {
    char* name;
    char shorten_name;
    void (*func)(char* params[], int params_len);
} Flag;

typedef struct ll_Flag ll_Flag; // forward declaration

typedef struct ll_Flag { // linked list
    Flag *data;
    ll_Flag *next;
} ll_Flag;

void parse_flags(int argc, char* argv[]);