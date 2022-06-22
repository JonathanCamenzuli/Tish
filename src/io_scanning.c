#include "io_scanning.h"
#include <stdlib.h>
#include <stdio.h>

char* tokenizer(char* inputBuffer)
{
    char* string = (char*)malloc(sizeof(char));
    char** args = (char**)malloc(sizeof(char*));

    for (char *ch = inputBuffer; *ch != '\0'; ch++)
    {
        switch (*ch)
        {
        case SPACE_CHAR:
            break;
        case QMARK_CHAR:
            while (*++ch != QMARK_CHAR)
            {
                if (*ch == BSLASH_CHAR && (*(ch+1) == QMARK_CHAR || *(ch+1) == BSLASH_CHAR || *(ch+1) == SCOLON_CHAR))
                {
                    string = (char*)realloc(string, sizeof(char)*(sizeof(string)/sizeof(string[0]))+1);
                    string[(sizeof(string)/sizeof(string[0]))-1] = *++ch;
                    string[sizeof(string)/sizeof(string[0])] = NULL_CHAR;
                }
                else
                {
                    string = (char*)realloc(string, sizeof(char)*(sizeof(string)/sizeof(string[0]))+1);
                    string[(sizeof(string)/sizeof(string[0]))-1] = *ch;
                    string[sizeof(string)/sizeof(string[0])] = NULL_CHAR;
                }
            }
            break;
        case BSLASH_CHAR:
            if (*(ch+1) == QMARK_CHAR || *(ch+1) == BSLASH_CHAR)
            {
                string = (char*)realloc(string, sizeof(char)*(sizeof(string)/sizeof(string[0]))+1);
                string[(sizeof(string)/sizeof(string[0]))-1] = *++ch;
                string[sizeof(string)/sizeof(string[0])] = NULL_CHAR;
            }
            break;
        default:
            string = (char*)realloc(string, sizeof(char)*(sizeof(string)/sizeof(string[0]))+1);
            string[(sizeof(string)/sizeof(string[0]))-1] = *ch;
            string[sizeof(string)/sizeof(string[0])] = NULL_CHAR;
            break;
        }
    }
    if ((sizeof(string)/sizeof(string[0])) > 1)
    {
        args = (char**)realloc(args, sizeof(char*)*(sizeof(args)/sizeof(args[0]))+1);
        args[(sizeof(args)/sizeof(args[0]))-1] = strdup(string);
        args[(sizeof(args)/sizeof(args[0]))+1] = NULL;
    }
    
    free(string);
    return args;
}

char*** pipelineTokenizer(char** args)
{
    int pipeSize = 1;
    int argSize = 1;

    char*** command = (char***)calloc(pipeSize+1, sizeof(char**));

    for (char** ch = args; *ch != NULL; ch++)
    {
        if (strcmp(*ch, VBAR_CHAR))
        {
            command = (char***)realloc(command, (++pipeSize+1)*sizeof(char**));
            command[pipeSize-1] = NULL;
            argSize = 1;
        }
        else
        {
            command = (char**)realloc(command, (++pipeSize+1)*sizeof(char**));
            command[pipeSize-1][pipeSize-2] = *ch;
            command[pipeSize-1][pipeSize-1] = NULL;
        }
    }

    command[pipeSize] = NULL;
    return command;
}

void freePipeline(char*** pipeline)
{
    for (char*** ch = pipeline; *ch != NULL; ch++)
        free(*ch);
    free(pipeline);
}
