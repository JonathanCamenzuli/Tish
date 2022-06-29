/**
 * @file commands.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Shell Built-in Commands (Task 2)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __COMMANDS_H
#define __COMMANDS_H

#define TISH_COMMANDS_NO 4

/**
 * @brief A data structure that represents a function used in a command
 * 
 */
typedef int (*tishFunction_t)(char **);

/**
 * @brief A struct that a tish command
 * 
 */
typedef struct 
{
    char *name;             /**< the name of the command itself */
    tishFunction_t func;    /**< the function which corresponds to the command */
}tishCommand_t;

/**
 * @brief Terminates the shell
 * 
 * @param args Arguments: Ignored
 * @return int Special code indicating shell being terminated (2)
 */
int exit_tish(char **args);


/**
 * @brief Changes the current working directory
 * 
 * @param args Arguments: Contain the path to be changed. If empty, directory is changed to HOME
 */
int cd_tish(char **args);

/**
 * @brief Prints the current working directory
 * 
 * @param args Arguments: Ignored
 */
int cwd_tish(char **args);

/**
 * @brief Prints information about tish (NOT FULLY IMPLEMENTED)
 * 
 * @param args Arguments: Ignored
 */
int ver_tish(char **args);

/**
 * @brief Launches a built-in command
 * 
 * @param args Argument/s
 * @return int 0 if successful, 1 if failed
 */
int execTishCommand(char **args);

#endif