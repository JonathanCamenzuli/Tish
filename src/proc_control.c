#include "proc_control.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>

int reopen(int fd, char* pathName, int flags, mode_t mode)
{
    // Big thanks to Dr. Keith Bugeja for kindly providing
    // this method: https://www.youtube.com/watch?v=XflfgbUiHYI
    int openFd = open(pathName, flags, mode);
    if ((openFd == fd) || (openFd < 0))
        return openFd;

    int dupFd = dup2(openFd, fd);
    close(openFd);

    if (dupFd == -1)
        return dupFd;
    else
        return fd;
}

int redirectInput(char* input)
{
    // Big thanks to Dr. Keith Bugeja for kindly providing
    // this method: https://www.youtube.com/watch?v=XflfgbUiHYI
    return(reopen(STDIN_FILENO, input, O_RDONLY, S_IRUSR));
}

int redirectOutput(char* output, int appendFlag)
{
    // Big thanks to Dr. Keith Bugeja for kindly providing
    // this method: https://www.youtube.com/watch?v=XflfgbUiHYI
    return(reopen(STDOUT_FILENO, output, appendFlag | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
}

int forkExecPipe(char ***pipelineArgs, char* fileIn, char* fileOut, bool appendOut, bool asyncEnable)
{
    int childCount = 0;

    char*** arg = pipelineArgs;
    while (*arg != NULL)
    {
        childCount++;
        arg++;
    }

    int pipeCount = childCount - 1;
    int fd[pipeCount * 2], *currFd = fd, *prevFd = NULL;

    int stage = 0;
    while (stage < childCount)
    {
        prevFd = currFd - 2;

        if (stage < pipeCount)
        {
            if (pipe(currFd) == -1)
            {
                perror("-tish: pipe() failed");
                return EXIT_FAILURE;
            }
        }

        pid_t childPID = fork();

        if (childPID == -1)
        {
            perror("-tish: fork() failed");
            return EXIT_FAILURE;
        }

        // Child Process
        else if (childPID == 0)
        {
            // All stages except the last
            if (stage < pipeCount)
            {
                if (close(currFd[0]) == -1)
                {
                    perror("-tish: close() failed");
                    return EXIT_FAILURE;                    
                }
                if (dup2(currFd[1], STDOUT_FILENO) == -1)
                {
                    perror("-tish: dup2() failed");
                    return EXIT_FAILURE;                    
                }
                if (close(currFd[1]) == -1)
                {
                    perror("-tish: close() failed");
                    return EXIT_FAILURE;
                }
            }

            // Set up input redirection (First stage)
            if (stage == 0 && fileIn != NULL)
            {
                
                if (redirectInput(fileIn) == -1)
                {
                    perror("-tish: redirect failed!");
                    return EXIT_FAILURE;
                }
            }
            // Set up Output Redirection (Last stage)
            else if (stage == pipeCount && fileOut != NULL)
            {   
                
                int returnOut;
                if (appendOut)
                    // Append Output Redirection
                    returnOut = redirectOutput(fileOut, O_RDWR | O_APPEND);
                else
                    returnOut = redirectOutput(fileOut, O_RDWR | O_TRUNC);
                
                if (returnOut == -1)
                {
                    perror("-tish: redirecting output failed");
                    return EXIT_FAILURE;
                }
            }

            // All stages except the first
            if (stage > 0)
            {
                if (close(prevFd[1]) == -1)
                {
                    perror("-tish: close() failed");
                    return EXIT_FAILURE;                    
                }
                if (dup2(prevFd[0], STDIN_FILENO) == -1)
                {
                    perror("-tish: dup2() failed");
                    return EXIT_FAILURE;                    
                }
                if (close(prevFd[0]) == -1)
                {
                    perror("-tish: close() failed");
                    return EXIT_FAILURE;
                }
            }

            // Execution!
            if (execvp(pipelineArgs[stage][0], pipelineArgs[stage]) == -1)
            {
                perror("-tish: execvp() failed");
                exit(EXIT_FAILURE);
            }
            return EXIT_SUCCESS;
        }
        
        // Parent Process
        if (stage >= 1)
        {
            if (close(prevFd[0]) == -1 || close(prevFd[1]) == -1)
            {
                perror("-tish: close() failed");
                return EXIT_FAILURE;
            }
        }

        currFd += 2;

        int status;
        if (!asyncEnable)
        {
            if (waitpid(childPID, NULL, 0) == -1)
            {
                perror("-tish: waitpid() failed");
                return EXIT_FAILURE;
            }
        }

        stage++;
    }

    return EXIT_SUCCESS;
}