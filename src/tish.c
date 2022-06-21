#include "io_scanning.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    while(1)
    {
        if (processInputExec() == EXIT_FAILURE)
        {
            fprintf(stderr, "-tish: execution failed\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}