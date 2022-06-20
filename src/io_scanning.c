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

int validateTishInput(char* inputBuffer, execVars_t* execVars)
{
    for (int i = 0; i < strlen(inputBuffer); i++)
    {
        // First and last argument cannot be metacharacters
        if (i == 0
            || i == strlen(inputBuffer)- 2 
            && inputBuffer[i] == GT_CHAR
            && inputBuffer[i+1] == GT_CHAR)
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c%c\'\n", GT_CHAR, GT_CHAR);
            return EXIT_FAILURE;
        }

        if ((i == 0 || i == strlen(inputBuffer) - 1)
            && (inputBuffer[i+2] == VBAR_CHAR
                || inputBuffer[i+2] == GT_CHAR
                || inputBuffer[i+2] == LT_CHAR
                || (i == 0 && inputBuffer[i] == SCOLON_CHAR)))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[i]);
            return EXIT_FAILURE;
        }
        
        // Disallow adjacent metacharacters
        if (!(execVars->metacharQuote)
            && i < strlen(inputBuffer) - 2
            && inputBuffer[i] == GT_CHAR
            && inputBuffer[i + 1] == GT_CHAR
            && (inputBuffer[i + 2] == VBAR_CHAR
                || inputBuffer[i + 2] == GT_CHAR
                || inputBuffer[i + 2] == LT_CHAR
                || inputBuffer[i + 2] == SCOLON_CHAR))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[i]);
            return EXIT_FAILURE;
        }

        if (!(execVars->metacharQuote)
            && !(inputBuffer[i] == GT_CHAR)
            && inputBuffer[i+1] == GT_CHAR
            && (inputBuffer[i] == VBAR_CHAR
                || inputBuffer[i] == GT_CHAR
                || inputBuffer[i] == LT_CHAR
                || inputBuffer[i] == SCOLON_CHAR)
            && (inputBuffer[i+1] == VBAR_CHAR
                || inputBuffer[i+1] == GT_CHAR
                || inputBuffer[i+1] == LT_CHAR
                || inputBuffer[i+1] == SCOLON_CHAR))
        {
            fprintf(stderr, "-tish: syntax error near unexpected token \'%c\'\n", inputBuffer[i]);
            return EXIT_FAILURE;
        }

        //Check if Metachar
        // Pipe
        if (!(execVars->metacharQuote) && inputBuffer[i] == VBAR_CHAR)
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
                    fprintf(stderr, "-tish: too many commands in pipeline [%s...|%s...|...]\n", execVars->pipeline[i - (execVars->commandPipeCount - 1)][0]
                        , execVars->pipeline[i - (execVars->commandPipeCount)][0]);
                    execVars->waitForSColon = true;
                    execVars->exec = false;
                    continue;
                }

                if (execVars->outRedir)
                {
                    if (execVars->metacharOutRedir)
                        continue;
                    else
                    {
                        execVars->fileOut[execVars->out_i] = '\0';
                        execVars->outRedir = false;
                        execVars->metacharOutRedir = false;
                        continue;
                    }
                }

                if (execVars->metacharInRedir)
                {
                    if (execVars->inRedirWait)
                        continue;
                    else
                    {
                        execVars->fileIn[execVars->in_i] = '\0';
                        execVars->metacharInRedir = false;
                        execVars->inRedirWait = false;
                        continue;
                    }
                }

                execVars->metacharPipe = true;
                execVars->metacharOutRedir = false;
                execVars->metacharInRedir = false;

                execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
                execVars->pipeline[execVars->command_i][execVars->arg_i + 1] = NULL;

                execVars->command_i++;
                execVars->arg_i = 0;
                execVars->char_i = 0;

                execVars->commandPipeCount++;

                continue;
            }
            else
                continue;
        }

        //Append Out
        else if(!execVars->metacharQuote && inputBuffer[i] == GT_CHAR && inputBuffer[i+1] == GT_CHAR)
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

            execVars->metacharPipe = false;
            execVars->metacharOutRedir = true;
            execVars->outRedir = true;
            execVars->appendOut = true;
            execVars->outRedirWait = true;
            execVars->pipeline[execVars->command_i][execVars->arg_i][execVars->char_i] = '\0';
            execVars->pipeline[execVars->command_i][execVars->arg_i + 1] = NULL;

            execVars->char_i++;
            continue;
        }

        //Output Redirect
        else if (!(execVars->metacharQuote) && inputBuf)
    }
    
    
}
