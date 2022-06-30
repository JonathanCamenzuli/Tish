#include "tfetch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

char asciiTishLogo[LOGO_ROWS][LOGO_COLS] = {
    "   /$$     /$$           /$$      ",
    "  | $$    |__/          | $$      ",
    " /$$$$$$   /$$  /$$$$$$$| $$$$$$$ ",
    "|_  $$_/  | $$ /$$_____/| $$__  $$",
    "  | $$    | $$|  $$$$$$ | $$  \\ $$",
    "  | $$ /$$| $$ \\____  $$| $$  | $$",
    "  |  $$$$/| $$ /$$$$$$$/| $$  | $$",
    "   \\___/  |__/|_______/ |__/  |__/",
    "                                   ",
    };

void getTfetchTitle(char* tfetchTitle)
{
    strcat(tfetchTitle, GREEN_ANSI);
    strcat(tfetchTitle, getenv("USER"));
    strcat(tfetchTitle, RESET_ANSI);
    strcat(tfetchTitle, "@");
    strcat(tfetchTitle, GREEN_ANSI);
    strcat(tfetchTitle, "tish");
    strcat(tfetchTitle, RESET_ANSI);
}

void getLineUnderTitle(char* lines)
{
    int count = 1;
    char tfetchTitle[TF_STR_BUFFER_LEN];

    strcat(tfetchTitle, getenv("USER"));
    strcat(tfetchTitle, "@");
    strcat(tfetchTitle, "tish\0");

    for (int i = 0; i < strlen(tfetchTitle); i++)
    {  
        if (tfetchTitle[i] != '\n')  
            count++;  
    } 

    for (int i = 0; i < (count - 1); i++)
        strcat(lines, "-");
}

void getOS(char* osStr)
{
    char* os = malloc(TF_STR_BUFFER_LEN);
    char* name = malloc(TF_STR_BUFFER_LEN);
    char* line = NULL;

    size_t len;

    struct utsname uname_t;
    uname(&uname_t);

    FILE* osRelease = fopen("/etc/os-release", "r");
    while (getline(&line, &len, osRelease) != -1)
    {
        if (sscanf(line, "PRETTY_NAME=\"%[^\"]+", name) > 0)
            break;
    }

    free(line);
    fclose(osRelease);
    snprintf(os, TF_STR_BUFFER_LEN, "%s %s", name, uname_t.machine);
    free(name);

    strcat(osStr, GREEN_ANSI);
    strcat(osStr, "Operating System");
    strcat(osStr, RESET_ANSI);
    strcat(osStr, ": ");
    strcat(osStr, os);
    strcat(osStr, uname_t.machine);
    strcat(osStr, RESET_ANSI);
}

void getKernel(char* kernelStr)
{
    struct utsname uname_t;
    uname(&uname_t);

    strcat(kernelStr, GREEN_ANSI);
    strcat(kernelStr, "Kernel");
    strcat(kernelStr, RESET_ANSI);
    strcat(kernelStr, ": ");
    strcat(kernelStr, uname_t.release);
    strcat(kernelStr, RESET_ANSI);
}

void getShell(char* shellStr)
{
    struct utsname uname_t;
    strcat(shellStr, GREEN_ANSI);
    strcat(shellStr, "Shell");
    strcat(shellStr, RESET_ANSI);
    strcat(shellStr, ": ");
    strcat(shellStr, getenv("SHELL"));
    strcat(shellStr, RESET_ANSI);
}

void tfetch(void)
{
    char tfetchTitle[TF_STR_BUFFER_LEN];
    char linesUnderTitle[TF_STR_BUFFER_LEN];
    char os[TF_STR_BUFFER_LEN];
    char kernel[TF_STR_BUFFER_LEN];
    char shell[TF_STR_BUFFER_LEN];

    getTfetchTitle(tfetchTitle);
    getLineUnderTitle(linesUnderTitle);
    getOS(os);
    getKernel(kernel);
    getShell(shell);

    printf("\n\n%s   %s\n", asciiTishLogo[0], tfetchTitle);
    printf("%s   %s\n", asciiTishLogo[1], linesUnderTitle);
    printf("%s   %s\n", asciiTishLogo[2], os);
    printf("%s   %s\n", asciiTishLogo[3], kernel);
    printf("%s   %s\n", asciiTishLogo[4], shell);
    printf("%s   %sAuthor%s: Jonathan Camenzuli, 2022\n", asciiTishLogo[5], GREEN_ANSI, RESET_ANSI);
    printf("%s     \n", asciiTishLogo[6]);
    printf("%s   I wish that I was able to \e[0;31mco\e[0;32mlo\e[0;33mur\e[0;34mis\e[0;35me%s the $s\n", asciiTishLogo[7], RESET_ANSI);
    printf("%s  in the tish logo but I had no time :(\n\n", asciiTishLogo[8]);
}