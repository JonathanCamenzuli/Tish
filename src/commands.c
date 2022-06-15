#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void exit_tish(char **args)
{
    exit(EXIT_SUCCESS);
}

void cd_tish(char **args)
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

void cwd_tish(char **args)
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