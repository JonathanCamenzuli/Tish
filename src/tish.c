#include "io_scanning.h"
#include "../libs/linenoise.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_TISH_PROMPT_LEN     4096
#define MAX_UNAME_LEN           16

int main(void)
{
    char cwd[MAX_CWD_PATH];
    char user[MAX_UNAME_LEN];
    char tishPrompt[MAX_TISH_PROMPT_LEN];
    char* tishLine;

    refreshTishPrompt(tishPrompt, user, cwd);

    while ((tishLine = linenoise(tishPrompt)) != NULL)
    {
        if (tishLine[0] != NULL_CHAR)
        {
            processTishInput(tishLine);
            refreshTishPrompt(tishPrompt, user, cwd);
        }
        free(tishLine);
    }

    return EXIT_SUCCESS;
}