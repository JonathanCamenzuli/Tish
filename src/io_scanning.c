#include "io_scanning.h"
#include "commands.h"
#include "proc_control.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char specialTishChars[] = {'~', '`', '#', '$', '&', '*',
                                 '(', ')', '[', ']', '{', '}',
                                 ':', '=', '?', '/', '!', '@',
                                 '+', '\'','\"', '\\', '|',
                                 '>', '<', ';'};

string_t* initStr()
{
    string_t* str;
    str = (string_t*)malloc(sizeof(string_t));
    str->string = (char*)malloc(sizeof(char));
    str->string[0] = NULL_CHAR;
    str->size = 1;
    return str;
}

args_t* initArgs()
{
    args_t* args;
    args = (args_t*)malloc(sizeof(args_t));
    args->arguments[0] = NULL_CHAR;
    args->size = 1;
    return args;
}

args_t* tokenizer(char* inputBuffer)
{
    string_t* str = initStr();
    args_t* args = initArgs();

    for (char *ch_i = inputBuffer; *ch_i != '\0'; ch_i++)
    {
        switch (*ch_i)
        {
        case SPACE_CHAR:
            //append to args(args, str)
            if (str->size > 1)
            {
                args->arguments = (char**)realloc(args->arguments, sizeof(char*)*(args->size+1));
                args->arguments[args->size-1] = strdup(str->string);
                args->arguments[args->size++] = NULL;
                str->size = 1;
            }
            break;
        case QMARK_CHAR:
            while (*++ch_i != QMARK_CHAR)
            {
                if (*ch_i == BSLASH_CHAR && (*(ch_i+1) == QMARK_CHAR || *(ch_i+1) == BSLASH_CHAR || *(ch_i+1) == SCOLON_CHAR))
                {
                    //append to string(str, *++ch_i)
                    str->string = (char*)realloc(str->string, sizeof(char)*(str->size+1));
                    str->string[str->size-1] = *++ch_i;
                    str->string[str->size] = '\0';
                    str->size++;
                }
                else
                {
                    //append to string(str, *ch_i)
                    str->string = (char*)realloc(str->string, sizeof(char)*(str->size+1));
                    str->string[str->size-1] = *ch_i;
                    str->string[str->size] = '\0';
                    str->size++;
                }
            }
            break;
        case BSLASH_CHAR:
            if (*(ch_i+1) == QMARK_CHAR || *(ch_i+1) == BSLASH_CHAR)
            {
                //append to string(str, *++ch_i)
                str->string = (char*)realloc(str->string, sizeof(char)*(str->size+1));
                str->string[str->size-1] = *++ch_i;
                str->string[str->size] = '\0';
                str->size++;
            }
            break;
        default:
            //append to string(str, *ch_i)
            str->string = (char*)realloc(str->string, sizeof(char)*(str->size+1));
            str->string[str->size-1] = *ch_i;
            str->string[str->size] = '\0';
            str->size++;
            break;
        }
    }

    if (str->size > 1)
    {
        args->arguments = (char**)realloc(args->arguments, sizeof(char*)*(args->size+1));
        args->arguments[args->size-1] = strdup(str->string);
        args->arguments[args->size++] = NULL;
        str->size = 1;
    }
    
    free(str->string);
    free(str);
    return args;
}

char*** pipelineTokenizer(char** args)
{
    int pipeSize = 1;
    int argSize = 1;

    char*** command = (char***)calloc(pipeSize+1, sizeof(char**));

    for (char** ch_i = args; *ch_i != NULL; ch_i++)
    {
        if (strcmp(*ch_i, "|"))
        {
            command = (char***)realloc(command, (++pipeSize+1)*sizeof(char**));
            command[pipeSize-1] = NULL;
            argSize = 1;
        }
        else
        {
            command = (char***)realloc(command, (++pipeSize+1)*sizeof(char**));
            command[pipeSize-1][pipeSize-2] = *ch_i;
            command[pipeSize-1][pipeSize-1] = NULL;
        }
    }

    command[pipeSize] = NULL;
    return command;
}

void freePipeline(char*** pipeline)
{
    for (char*** ch_i = pipeline; *ch_i != NULL; ch_i++)
        free(*ch_i);
    free(pipeline);
}

bool isRedirFileValid(char** fileName)
{
    bool redirect = false;
    bool isFilenameValid = false;

    for (char** ch_i = fileName; *ch_i != NULL; ch_i++)
    {
        if (strchr(*ch_i, '<') != NULL || strcmp(*ch_i, ">>") == 0 || strchr(*ch_i, '<') != NULL)
            redirect = true;

        for (int i = 0; i < (sizeof(specialTishChars)/sizeof(char)); i++)
        {
            if (strchr(*(ch_i+1), specialTishChars[i]) != NULL)
                isFilenameValid = true;
        }
        
        if (redirect && isFilenameValid)
            return false;
    }
    return true;

}

int getRedirType(char* token)
{
    if (strchr(token, '>') != NULL)
        return 1;
    else if (strcmp(token, ">>") == 0)
        return 2;
    else if (strchr(token, '<') != NULL)
        return 3;
    else
        return 0;
}

void createPipeline(char* inputBuffer)
{
    args_t* args = tokenizer(inputBuffer);
    char** tokens = args->arguments;

    int token_i = 0;
    int tishExitCode = 0;

    char* fileOut;
    char* fileIn;
    bool appendOut;

    for (char** ch_i = tokens; *ch_i != NULL; ch_i++)
        token_i++;

    if (strcmp(tokens[0], ">") == 0
            || strcmp(tokens[0], ">>") == 0
            || strcmp(tokens[0], "<") == 0
            || strcmp(tokens[0], "|") == 0)
        fprintf(stderr, "-tish: syntax error near unexpected token \'%s\'\n", tokens[0]);
    else if (strcmp(tokens[token_i-1], ">") == 0
                || strcmp(tokens[token_i-1], ">>") == 0
                || strcmp(tokens[token_i-1], "<") == 0
                || strcmp(tokens[token_i-1], "|") == 0)
        fprintf(stderr, "-tish: syntax error near unexpected token \'%s\'\n", tokens[token_i-1]);
    else if (isRedirFileValid(tokens))
    {
        tishExitCode = execTishCommand(tokens);
        if (tishExitCode == 2)
        {
            free(inputBuffer);
            free(args);
            exit(EXIT_SUCCESS);
        }
        else if (tishExitCode == 1)
        {
            fileIn = NULL;
            fileOut = NULL;
            appendOut = false;

            for (char** ch_i = tokens; *ch_i != NULL; ch_i++)
            {
                int redirType = getRedirType(*ch_i);
                if (redirType == 1)
                {
                    fileOut = strdup(*(ch_i+1));
                    for (char** newArgs = ch_i; *newArgs != NULL; newArgs++)
                        *newArgs = *(newArgs+2);
                    args->size -= 2;
                    ch_i -= 2;
                }
                else if (redirType == 2)
                    appendOut = true;
                else if (redirType == 3)
                {
                    fileIn = strdup(*(ch_i+1));
                    for (char** newArgs = ch_i; *newArgs; newArgs++)
                        *newArgs = *(newArgs+2);
                    args->size -= 2;
                    ch_i -= 2;
                }
            }
            char*** pipeline = pipelineTokenizer(tokens);
            forkExecPipe(pipeline, fileIn, fileOut, appendOut, false);
            free(fileOut);
            free(fileIn);
            freePipeline(pipeline);
        }
    }
    else
        fprintf(stderr, "-tish: syntax error: invalid filename\n");
    free(args);
}

void processTishInput(char* input)
{
    char* inputBuffer = input;
    for (char* ch_i = input; *ch_i; ch_i++)
        if (*ch_i == BSLASH_CHAR && *(ch_i+1) == SCOLON_CHAR)
            ch_i++;
        else if (*ch_i == SCOLON_CHAR)
        {
            *ch_i = NULL_CHAR;
            createPipeline(inputBuffer);
            inputBuffer = ch_i++;
        }
        else if (*(ch_i+1) == NULL_CHAR)
            createPipeline(inputBuffer);
}

int refreshTishPrompt(char* tishPrompt, char* user, char* cwd)
{
    tishPrompt[0] = NULL_CHAR;

    if (getcwd(cwd, MAX_CWD_PATH))
    {
        strcat(tishPrompt, GREEN_ANSI);
        strcat(tishPrompt, user);
        strcat(tishPrompt, "@tish");
        strcat(tishPrompt, RESET_ANSI);
        strcat(tishPrompt, BLUE_ANSI);
        strcat(tishPrompt, ":");
        strcat(tishPrompt, cwd);
        strcat(tishPrompt, RESET_ANSI);
        strcat(tishPrompt, "$ ");
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "-tish: cannot get current working directory\n");
        return EXIT_FAILURE;
    }
}