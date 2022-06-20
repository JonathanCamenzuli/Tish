#include "io_scanning.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int getTishInput(char* inputBuffer)
{
    if (!fgets(inputBuffer, MAX_TISH_INPUT, stdin))
    {
        fprintf(stderr, "fgets() failed.\n");
        return EXIT_FAILURE;
    }

    int lastElem = strlen(inputBuffer) - 1;
    inputBuffer[lastElem] = '\0';
    return EXIT_SUCCESS;
}

int validateTishInput(char* inputBuffer, int index_i, execVars_t* execVars)
{
    // First and last argument cannot be metacharacters
    if ((index_i == 0 || index_i == strlen(inputBuffer) - 2) 
        && (inputBuffer[index_i] == GT_CHAR)
        && (inputBuffer[index_i+1] == GT_CHAR))
    {
        fprintf(stderr, "-tish: syntax error near unexpected token \'%c%c\'\n", GT_CHAR, GT_CHAR);
        return EXIT_FAILURE;
    }

    if ((index_i == 0 || index_i == strlen(inputBuffer) - 1)
        && (inputBuffer[index_i+2] == VBAR_CHAR || inputBuffer[index_i+2] == GT_CHAR || inputBuffer[index_i+2] == LT_CHAR || (index_i == 0 && inputBuffer[index_i] == SCOLON_CHAR)))
    {
        fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[index_i]);
        return EXIT_FAILURE;
    }
    
    // Disallow adjacent metacharacters
    if (!(execVars->metacharQuote)
        && (index_i < strlen(inputBuffer) - 2)
        && inputBuffer[index_i] == GT_CHAR
        && inputBuffer[index_i+1] == GT_CHAR
        && (inputBuffer[index_i+2] == VBAR_CHAR || inputBuffer[index_i + 2] == GT_CHAR || inputBuffer[index_i + 2] == LT_CHAR || inputBuffer[index_i + 2] == SCOLON_CHAR))
    {
        fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[index_i]);
        return EXIT_FAILURE;
    }

    if (!(execVars->metacharQuote)
        && !(inputBuffer[index_i] == GT_CHAR)
        && inputBuffer[index_i+1] == GT_CHAR
        && (inputBuffer[index_i] == VBAR_CHAR || inputBuffer[index_i] == GT_CHAR || inputBuffer[index_i] == LT_CHAR || inputBuffer[index_i] == SCOLON_CHAR)
        && (inputBuffer[index_i+1] == VBAR_CHAR || inputBuffer[index_i+1] == GT_CHAR || inputBuffer[index_i+1] == LT_CHAR || inputBuffer[index_i+1] == SCOLON_CHAR))
    {
        fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[index_i]);
        return EXIT_FAILURE;
    }

    // Checking for 'Append output redirection' (>>) metacharacters
    if(!execVars->metacharQuote && inputBuffer[index_i] == GT_CHAR && inputBuffer[index_i+1] == GT_CHAR)
    {
        if (!(execVars->charFound))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c%c\'\n", GT_CHAR, GT_CHAR);
            return EXIT_FAILURE;
        }
        if (execVars->outRedir)
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c%c\'\n", GT_CHAR, GT_CHAR);
            return EXIT_FAILURE;                
        }

        *execVars = (execVars_t)
        {
            .metacharPipe = false,
            .metacharOutRedir = true,
            .outRedir = true,
            .appendOut = true,
            .outRedirWait = true
        };

        execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
        execVars->pipeline[execVars->command_i][execVars->arg_i+1] = NULL;

        execVars->char_i++;
        return 2;
    }

    // Checking for 'Output redirection' (>) metacharacter
    else if (!(execVars->metacharQuote) && inputBuffer[index_i] == GT_CHAR)
    {
        if (!(execVars->charFound))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", GT_CHAR);
            return EXIT_FAILURE;                  
        }
        if (execVars->outRedir)
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[index_i]);
            return EXIT_FAILURE;    
        }

        *execVars = (execVars_t)
        {
            .metacharPipe = false,
            .metacharOutRedir = true,
            .outRedir = true,
            .outRedirWait = true,
        };

        execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
        execVars->pipeline[execVars->command_i][execVars->arg_i+1] = NULL;
        return 2;;
    }
    // Checking for 'Input Redirection' (<) metacharacter
    else if (!(execVars->metacharQuote) && inputBuffer[index_i] == LT_CHAR)
    {
        if (!(execVars->charFound))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", LT_CHAR);
            return EXIT_FAILURE; 
        }
        if (execVars->inRedir)
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[index_i]);
            return EXIT_FAILURE;    
        }

        *execVars = (execVars_t)
        {
            .inRedir = true,
            .metacharPipe = false,
            .metacharOutRedir = false,
            .metacharInRedir = true,
            .inRedirWait = true,
        };

        execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
        execVars->pipeline[execVars->command_i][execVars->arg_i+1] = NULL;

        return 2;;
    }
    // Checking for 'Pipe operator' (|) metacharacter
    else if (!(execVars->metacharQuote) && inputBuffer[index_i] == VBAR_CHAR)
    {
        if (!(execVars->charFound))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", VBAR_CHAR);
            return EXIT_FAILURE;
        }
        if (execVars->pipe)
        {
            if (execVars->commandPipeCount >= MAX_TISH_COMMANDS)
            {
                fprintf(stderr, "-tish: too many commands in pipeline [%s...|%s...|...]\n", execVars->pipeline[index_i - (execVars->commandPipeCount - 1)][0]
                    , execVars->pipeline[index_i - (execVars->commandPipeCount)][0]);
                execVars->waitForSColon = true;
                execVars->exec = false;
                return 2;
            }

            if (execVars->outRedir)
            {
                if (execVars->metacharOutRedir)
                    return 2;
                else
                {
                    execVars->fileOut[execVars->out_i] = '\0';
                    execVars->outRedir = false;
                    execVars->metacharOutRedir = false;
                    return 2;
                }
            }

            if (execVars->metacharInRedir)
            {
                if (execVars->inRedirWait)
                    return 2;
                else
                {
                    execVars->fileIn[execVars->in_i] = '\0';
                    execVars->metacharInRedir = false;
                    execVars->inRedirWait = false;
                    return 2;
                }
            }

            *execVars = (execVars_t)
            {
                .metacharPipe = true,
                .metacharOutRedir = false,
                .metacharInRedir = false,
                .arg_i = 0,
                .char_i = 0
            };

            execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
            execVars->pipeline[execVars->command_i][execVars->arg_i + 1] = NULL;

            execVars->command_i++;
            execVars->commandPipeCount++;

            return 2;
        }
        else
            return 2;
    }
    // Checking for 'New argument in input' ( ) metacharacter
    else if (!(execVars->metacharQuote) && inputBuffer[index_i] == SPACE_CHAR)
    {
        if ((execVars->arg_i + 1) >= MAX_TISH_ARGS)
        {
            fprintf(stderr, "-tish: %s: too many arguments passed\n", execVars->pipeline[index_i - (execVars->commandPipeCount-1)][0]);
            execVars->waitForSColon = true;
            execVars->exec = false;
            return 2;;
        }
        if (execVars->metacharOutRedir)
        {
            if (execVars->outRedirWait)
                return 2;
            else
            {
                execVars->fileOut[execVars->out_i] = '\0';
                execVars->metacharOutRedir = false;
                execVars->outRedirWait = false;
                return 2;
            }
        }
        if (execVars->metacharInRedir)
        {
            if (execVars->inRedirWait)
                return 2;
            else
            {
                execVars->fileIn[execVars->in_i] = '\0';
                execVars->metacharInRedir = false;
                execVars->inRedirWait = false;
                return 2;
            }
        }
        if (index_i == strlen(inputBuffer) - 1)
            return EXIT_SUCCESS;
        if ((index_i == 0 || index_i == strlen(inputBuffer)-1)
            || (execVars->arg_i == 0 && execVars->char_i == 0)
            || inputBuffer[index_i+1] == SPACE_CHAR
            || inputBuffer[index_i+1] == VBAR_CHAR
            || inputBuffer[index_i+1] == GT_CHAR
            || inputBuffer[index_i+1] == LT_CHAR
            || inputBuffer[index_i+1] == SCOLON_CHAR
            || inputBuffer[index_i-1] == VBAR_CHAR
            || inputBuffer[index_i-1] == GT_CHAR
            || inputBuffer[index_i-1] == LT_CHAR
            || inputBuffer[index_i-1] == SCOLON_CHAR)
            return 2;

        execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';

        execVars->arg_i++;
        execVars->char_i = 0;
        return 2;
    }
    
    // Checking for 'Quotation marks' (") as a metacharacter
    else if (inputBuffer[index_i] == QMARK_CHAR)
    {
        if (execVars->metacharQuote)
        {
            execVars->metacharQuote = false;
            return 2;
        }
        execVars->metacharQuote = true;
        return 2;
    }

    // Strip meaning of metacharacter (\)
    else if(inputBuffer[index_i] == BSLASH_CHAR)
    {
        if (execVars->char_i + 1 >= MAX_TISH_TOKEN_LEN)
        {
            fprintf(stderr, "-tish: too many characters passed to argument [%c%c%c%c...] in pipeline %d\n",
                execVars->pipeline[execVars->command_i][execVars->arg_i][0], execVars->pipeline[execVars->command_i][execVars->arg_i][1],
                execVars->pipeline[execVars->command_i][execVars->arg_i][2], execVars->pipeline[execVars->command_i][execVars->arg_i][3],
                execVars->pipeline[execVars->command_i][execVars->arg_i][4], execVars->command_i + 1);
            execVars->waitForSColon = true;
            execVars->exec = false;
            return 2;
        }
        execVars->pipeline[execVars->command_i][execVars->arg_i][(execVars->char_i)++] = inputBuffer[index_i+1];
        index_i++;
        return 2;
    }

    // Checking for 'separation of multiple command pipelines' (;) metacharacter
    else if (!(execVars->metacharQuote) && inputBuffer[index_i] == SCOLON_CHAR)
    {
        if (!(execVars->charFound))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%s\'\n", SCOLON_CHAR);
            return EXIT_FAILURE;
        }
        execVars->waitForSColon = false;
        if ((execVars->command_i + 1) >= MAX_TISH_COMMANDS)
        {
            fprintf(stderr, "-tish: too many pipelines passed to pipeline sequences\n");
            return EXIT_FAILURE; 
        }
        if (index_i == strlen(inputBuffer) - 1)
            return 2;;
        
        execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
        execVars->pipeline[execVars->command_i][execVars->arg_i+1] = NULL;

        if (execVars->outRedir)
            execVars->fileOut[strlen(execVars->fileOut)] = '\0';
        else
            execVars->fileOut = NULL;

        if (execVars->inRedir)
            execVars->fileIn[strlen(execVars->fileIn)] = '\0';
        else
            execVars->fileIn = NULL;

        char* fileInParam;
        char* fileOutParam;

        if (execVars->inRedir)
            fileInParam = execVars->fileIn;
        else
            fileInParam = NULL;

        if (execVars->outRedir)
            fileOutParam = execVars->fileOut;
        else
            fileOutParam = NULL;

        if ( ((execVars->commandPipeCount) == 1) && execTishCommand(**(execVars->pipeline + execVars->command_i), *(execVars->pipeline + execVars->command_i)) == 0)
        {
            free(execVars->fileOut);
            execVars->fileOut = malloc(MAX_FILENAME_LEN*sizeof(char));

            free(execVars->fileIn);
            execVars->fileIn = malloc(MAX_FILENAME_LEN*sizeof(char));


            *execVars = (execVars_t)
            {
                .outRedir = false,
                .inRedir = false,
                .appendOut = false,
                .pipe = false,
                .metacharPipe = false,
                .metacharOutRedir = false,
                .metacharInRedir = false,
                .metacharQuote = false,
                .arg_i = 0,
                .char_i = 0,
                .commandPipeCount = 1,
                .out_i = 0,
                .in_i = 0,
                .pipe = true,
                .outRedirWait = false,
                .inRedirWait = false
            };

            execVars->command_i++;

            return 2;
        }
        else if (forkExecPipe(execVars->pipeline + (execVars->command_i - (execVars->commandPipeCount - 1)), fileInParam, fileOutParam, execVars->appendOut, false) == 1)
        {
            fprintf(stderr, "-tish: execution failed\n");
            return EXIT_FAILURE;
        }
        else
        {
            free(execVars->fileOut);
            execVars->fileOut = malloc(MAX_FILENAME_LEN*sizeof(char));

            free(execVars->fileIn);
            execVars->fileIn = malloc(MAX_FILENAME_LEN*sizeof(char));

            *execVars = (execVars_t)
            {
                .outRedir = false,
                .inRedir = false,
                .appendOut = false,
                .pipe = true,
                .metacharPipe = false,
                .metacharOutRedir = false,
                .metacharInRedir = false,
                .metacharQuote = false,
                .arg_i = 0,
                .char_i = 0,
                .commandPipeCount = 1,
                .out_i = 0,
                .in_i = 0,
                .pipe = true,
                .outRedirWait = false,
                .inRedirWait = false
            };

            execVars->command_i++;

            return 2;
        }
        return 2;
    }
}