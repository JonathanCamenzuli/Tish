#include "commands.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "../libs/tfetch.h"

int exit_tish(char** args)
{
    for (char** ch = args; *ch != NULL; ch++)
        free(*ch);
    free(args);

    return 2;
}

int cd_tish(char** args)
{
    if (*args)
    {
        if (args[1] == NULL || strcmp(args[1], "~") == 0)
            chdir(getenv("HOME"));
        else if (chdir(args[1]) == -1)
        {
            printf("-tish: cd: %s: No such file or directory\n", args[1]);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int cwd_tish(char** args)
{
    char cwdStr[100];

    if (getcwd(cwdStr, 100))
        printf("%s\n", cwdStr);
    else
    {
        perror("getcwd failed!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

int ver_tish(char** args)
{
    setenv("SHELL", "Tiny Shell (tish) version 1.0", 1);
    tfetch();
    return EXIT_SUCCESS;
}

tishCommand_t execTishCommands[TISH_COMMANDS_NO] =
{
    {"exit", &exit_tish},
    {"cd", &cd_tish},
    {"cwd", &cwd_tish},
    {"ver", &ver_tish}
};

int execTishCommand(char** args)
{
    bool doesTishCommandExist = false;
    int returnTishFunction;
    for (int i = 0; i < TISH_COMMANDS_NO; i++)
    {
        if (strcmp(execTishCommands[i].name, args[0]) == 0)
        {
            doesTishCommandExist = true;
            returnTishFunction = execTishCommands[i].func(args);
            return returnTishFunction;
        }
    }

    return EXIT_FAILURE;
}