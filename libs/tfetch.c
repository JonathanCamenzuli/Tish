#include "tfetch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

const char ansiTishLogo[8][40] = {
    "   /$$     /$$           /$$      ",//OK
    "  | $$    |__/          | $$      ",//OK
    " /$$$$$$   /$$  /$$$$$$$| $$$$$$$ ",//OK
    "|_  $$_/  | $$ /$$_____/| $$__  $$",
    "  | $$    | $$|  $$$$$$ | $$  \\ $$",
    "  | $$ /$$| $$ \\____  $$| $$  | $$",
    "  |  $$$$/| $$ /$$$$$$$/| $$  | $$",
    "   \\___/  |__/|_______/ |__/  |__/",
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

void getLinesUnderTitle(char* lines)
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

void getColors(char* colours)
{
    char* colour = colours;

    for(int i = 0; i < 8; i++) {
        sprintf(colour, "\e[4%dm   ", i);
        colour += 8;
    }
    snprintf(colour, 5, "\e[0m");
}

void tfetch(void)
{
    char tfetchTitle[TF_STR_BUFFER_LEN];
    char linesUnderTitle[TF_STR_BUFFER_LEN];
    char os[TF_STR_BUFFER_LEN];
    char kernel[TF_STR_BUFFER_LEN];
    char shell[TF_STR_BUFFER_LEN];
    char colours[TF_STR_BUFFER_LEN];

    getTfetchTitle(tfetchTitle);
    getLinesUnderTitle(linesUnderTitle);
    getOS(os);
    getKernel(kernel);
    getShell(shell);
    getColors(colours);

    printf("%s   %s\n", ansiTishLogo[0], tfetchTitle);
    printf("%s   %s\n", ansiTishLogo[1], linesUnderTitle);
    printf("%s   %s\n", ansiTishLogo[2], os);
    printf("%s   %s\n", ansiTishLogo[3], kernel);
    printf("%s   %s\n", ansiTishLogo[4], shell);
    printf("%s     \n", ansiTishLogo[5]);
    printf("%s     \n", ansiTishLogo[6]);
    printf("%s   %s\n\n", ansiTishLogo[7], colours);
}