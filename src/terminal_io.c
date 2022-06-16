#include "terminal_io.h"
#include <stdlib.h>

string_t* init_str()
{
    string_t *str = (string_t*)malloc(sizeof(string_t));
    str->string = (char*)malloc(sizeof(char));
    str->size = 1;
    str->string[0] = '\0';
    return str;
}

int get_str_length(string_t* str)
{
    return str->size-1;
}

void print_str(string_t* str)
{
    for (int i = 0; i < str->size; i++)
        printf("%s", str->string[i]);
}

arg_t* init_arg()
{
    string_t *str = (string_t*)malloc(sizeof(string_t));
    str->string = (char*)malloc(sizeof(char));
    str->size = 1;
    str->string[0] = '\0';
    return str;
}



