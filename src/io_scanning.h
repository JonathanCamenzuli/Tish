/**
 * @file io_scanning.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Terminal Input and Output and Advanced Scanning (Tasks 3 & 4)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __IO_SCANNING_H
#define __IO_SCANNING_H

#include <stdbool.h>

#define SPACE_CHAR          ' '
#define QMARK_CHAR          '\"'
#define BSLASH_CHAR         '\\'
//#define VBAR_CHAR           '|'
#define GT_CHAR             '>'
//#define AOUT_REDIR_CHAR     '>>'
#define LT_CHAR             '<'
#define SCOLON_CHAR         ';'
#define NULL_CHAR           '\0'

#define GREEN_ANSI          "\e[0;32m"
#define BLUE_ANSI           "\e[0;34m"	
#define RESET_ANSI          "\e[0m"

#define MAX_CWD_PATH        2048


/**
 * @brief Special characters which are considered to be invalid
 *        characters for files
 * 
 */
extern const char specialTishChars[];

typedef struct
{
    char* string;
    int size;
}string_t;

typedef struct
{
    char** arguments;
    int size;
}args_t;


string_t* initStr();

args_t* initArgs();

void addToArgs(args_t* args, string_t* str);

void addToStr(string_t* str, char ch);

args_t* tokenizer(char* inputBuffer);

/**
 * @brief Tokenises the pipeline
 * 
 * @param args      Arguments present in put
 * @return char***  Command
 */
char*** pipelineTokenizer(char** args);

/**
 * @brief Frees the memory allocated to the pipline
 * 
 * @param pipeline Pipeline to free memory from
 */
void freePipeline(char*** pipeline);

bool isRedirFileValid(char** fileName);

/**
 * @brief Get the file redirection type
 * 
 * @param token 
 * @return int      1 - Output Redirection (>);
 *                  2 - Append Output Redirection (>>);
 *                  3 - Input Redirection (<);
 *                  0 - Invalid character
 */
int getRedirType(char* token);

void createPipeline(char* inputBuffer);

void processTishInput(char* input);

int refreshTishPrompt(char* tishPrompt, char* cwd);

#endif