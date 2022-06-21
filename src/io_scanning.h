/**
 * @file terminal_io.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Terminal Input and Output and Advanced Scanning (Tasks 3 & 4)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IO_SCANNING_H
#define IO_SCANNING_H

#include <limits.h>
#include <stdbool.h>

#define MAX_TISH_INPUT      512
#define MAX_TISH_PIPES      16
#define MAX_TISH_COMMANDS   16
#define MAX_TISH_ARGS       16
#define MAX_TISH_TOKEN_LEN  512
#define MAX_FILENAME_LEN    128

#define GT_CHAR             '>'
#define LT_CHAR             '<'
#define VBAR_CHAR           '|'
#define SPACE_CHAR          ' '
#define QMARK_CHAR          '\"'
#define BSLASH_CHAR         '\\'
#define SCOLON_CHAR         ';'      

/**
 * @brief Struct that contains all the variables used in the io_scanning src files
 * 
 */
typedef struct
{
    char*** pipeline;       /**< Contains the pipeline itself*/
    char* inputBuffer;      /**< A buffer which stores the input made from the user */
    int commandPipeCount;   /**< Keep track of command in the pipeline */
    int command_i;          /**< Index for commands */
    int arg_i;              /**< Index for arguments */
    int char_i;             /**< Index for characters */
    bool metacharPipe;      /**< Has a metacharacter for a pipe been found? */
    bool metacharOutRedir;  /**< Has a metacharacter for output redirection been found? */
    bool metacharInRedir;   /**< Has a metacharacter for input redirection been found? */
    bool metacharQuote;     /**< Have quotation marks been detected? ("...") */
    bool outRedir;          /**< Flag for output redirection */
    bool inRedir;           /**< Flag for input redirection */
    bool appendOut;         /**< Flag for append */
    bool pipe;              /**< Flag for creating a pipe */
    char* fileOut;          /**< File path for output redirection */
    char* fileIn;           /**< File path for input redirection */
    int out_i;              /**< Index for fileOut */
    int in_i;               /**< Index for fileIn */

    bool outRedirWait;      /**< */
    bool inRedirWait;       /**< */

    bool charFound;         /**< Flag which indicates that a character has been found */

    bool waitForSColon;     /**< */

    bool exec;               /**< Flag for execution */

}execVars_t;


/**
 * @brief Process terminal input into a buffer
 * 
 * @param inputBuffer   Buffer in which input is to stored
 * @return int          0 if successful, 1 if failure
 */
int getTishInput(char* inputBuffer);

/**
 * @brief Validates the input made by the user
 * 
 * @param inputBuffer   A buffer which stores the input made from the user
 * @param index_i       Index of ongoing loop
 * @param execVars      An instance of the execVars_t struct  
 * @return int          If 0, successful, if 1, failure, if 2, continue statement 
 */
int validateTishInput(char* inputBuffer, int index_i, execVars_t* execVars);

/**
 * @brief Process and execute user input
 * 
 * @return int  If 0, successful, if 1, failure
 */
int processInputExec();

#endif