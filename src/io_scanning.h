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
#define RED_ANSI            "\e[0;31m"			
#define RESET_ANSI          "\e[0m"

#define MAX_CWD_PATH        2048

/**
 * @brief Special characters which are considered to be invalid
 *        characters for files
 */
extern const char specialTishChars[];

/**
 * @brief A data structure that holds input which is meant to act
 *        as string/s
 */
typedef struct
{
    char* string;   /**< the contents of the string itself */
    int size;       /**< the size of the string itself */
}string_t;

/**
 * @brief A data structure that holds input which is meant to act
 *        as argument/s
 */
typedef struct
{
    char** arguments;   /**< the contents of the argument/s itself */
    int size;           /**< the size of the argument/s itself */
}args_t;

/**
 * @brief Initialises an instance of the string_t structure
 * 
 * @return string_t* An initialised instance of string_t
 */
string_t* initStr();

/**
 * @brief Initialises an instance of the args_t structure
 * 
 * @return args_t* An initialised instance of args_t
 */
args_t* initArgs();

/**
 * @brief This function serves as an adder function for args_t that appends
 *        'strings' that are supposed to act as arguments
 * 
 * @param args  an instance of args_t
 * @param str   an instance of string_t
 */
void addToArgs(args_t* args, string_t* str);

/**
 * @brief This function serves as an adder function for string_t that appends
 *        'strings' that are actually acting as strings (meant to be used in
 *        an iterative manner)
 * 
 * @param str   the instance of string_t
 * @param ch    a character to be appended to strings
 */
void addToStr(string_t* str, char ch);

/**
 * @brief Tokenises the input made by the user into strings (string_t) and
 *        arguments (args_t)
 * 
 * @param inputBuffer Self-explanory
 * @return args_t*    An instance of args_t
 */
args_t* tokenizer(char* inputBuffer);

/**
 * @brief Creates a pipeline which considers the pipe metacharacter (|) in
 *        the input
 * 
 * @param inputBuffer Self-explanory
 * @return char***    Tokenised Pipeline
 */
char*** pipelineTokenizer(char** inputBuffer);

/**
 * @brief Frees the memory allocated to the pipeline
 * 
 * @param pipeline Pipeline to free memory from
 */
void freePipeline(char*** pipeline);

/**
 * @brief Checks for redirection metacharacters (>, >>, <) and checks if the
 *        filename used for redirection has any valid characters
 * 
 * @param inputBuffer Self-explanory
 * @return true       Filename is valid and redirection metacharacters are
 *                    detected
 * @return false      Either filename is invalid or redirection metacharacters
 *                    are not detected
 */
bool isRedirValid(char** inputBuffer);

/**
 * @brief Get the file redirection type
 * 
 * @param token 
 * @return int      1 - Output Redirection (>),
 *                  2 - Append Output Redirection (>>),
 *                  3 - Input Redirection (<),
 *                  0 - Invalid character,
 */
int getRedirType(char* token);

/**
 * @brief Create a Pipeline object
 * 
 * @param inputBuffer Self-explanory 
 */
void createPipeline(char* inputBuffer);

/**
 * @brief Processes the input made by the user in Tiny Shell
 * 
 * @param inputBuffer Self-explanory
 */
void processTishInput(char* inputBuffer);

/**
 * @brief Provides the prompt which prompts the user to enter input in tish
 * 
 * @param tishPrompt String that will hold the prompt
 * @param cwd        String that will hold the current working directory
 * @return int       0 if cwd is found, 1 if cwd is not found
 */
int refreshTishPrompt(char* tishPrompt, char* cwd);

#endif