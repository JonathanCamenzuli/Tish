#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int forkExecPipe(char ***pipelineArgs[], char *fileIn, char *fileOut, bool appendOut, bool asyncEnable)
{
    int childCount = 0;

    char ***arg = pipelineArgs;
    while (*arg != NULL)
    {
        childCount++;
        arg++;
    }

    int pipeCount = childCount - 1;
    int fd[pipeCount * 2], *currFd = fd, *prevFd = NULL;

    for (int stage = 0; stage < childCount; stage++)
    {
        prevFd = currFd - 2;

        if ((stage < pipeCount) && (pipe(currFd) == -1))
        {
            perror("pipe unsuccessful!");
            return EXIT_FAILURE;
        }

        pid_t childPID = fork();

        if (childPID == -1)
        {
            perror("fork failed!");
            return EXIT_FAILURE;
        }
        else if (childPID == 0)
        {
            if ((stage == 0 && fileIn) && (redirect_input(fileIn) == -1))
            {
                perror("redirect failed!");
                return EXIT_FAILURE;
            }

            if (stage > pipeCount)
            {
                if (close(currFd[0]) == -1)
                {
                    perror("close failed!");
                    return EXIT_FAILURE;
                }

                if (dup2(currFd[1], STDERR_FILENO) == -1)
                {
                    perror("dup2 failed!");
                    return EXIT_FAILURE;
                }

                if (close(currFd[1] == -1))
                {
                    perror("close failed!");
                    return EXIT_FAILURE;
                }
            }

            if ((stage == pipeCount) && fileOut)
            {
                int returnOut;
                if (appendOut)
                    returnOut = redirect_output(fileOut, O_RDWR | O_APPEND);
                else
                    returnOut = redirect_output(fileOut, O_RDWR | O_TRUNC);

                if (returnOut == -1)
                {
                    perror("redirecting output failed!");
                    return EXIT_FAILURE;
                }
            }

            if (stage > 0)
            {
                if (close(prevFd[1] == -1))
                {
                    perror("close failed!");
                    return EXIT_FAILURE;
                }

                if (dup2(prevFd[0], STDIN_FILENO) == -1)
                {
                    perror("dup2 failed!");
                    return EXIT_FAILURE;
                }

                if (close(prevFd[0]) == -1)
                {
                    perror("close failed!");
                    return EXIT_FAILURE;
                }
            }

            if (execvp(**pipelineArgs, *pipelineArgs) == -1)
            {
                perror("exec failed!");
                exit(EXIT_FAILURE);
            }

            return EXIT_SUCCESS;
        }

        if ((stage >= 1) && (close(prevFd[0]) == -1 || close(prevFd[1]) == -1))
        {
            perror("close failed!");
            return EXIT_FAILURE;
        }

        int status;
        if (asyncEnable && (waitpid(childPID, &status, WNOHANG) == -1))
        {
            perror("waitpid failed!");
            return EXIT_FAILURE;
        }
        else if (waitpid(childPID, &status, WUNTRACED) == -1)
        {
            perror("waitpid failed!");
            return EXIT_FAILURE;
        }

        if (!WIFEXITED(status))
            return EXIT_FAILURE;

        currFd += 2;
    }

    return EXIT_SUCCESS;
}