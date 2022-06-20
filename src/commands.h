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
 */
void exit_tish(char **args);

/**
 * @brief Changes the current working directory
 * 
 * @param args Arguments: Contain the path to be changed. If empty, directory is changed to HOME
 */
void cd_tish(char **args);

/**
 * @brief Prints the current working directory
 * 
 * @param args Arguments: Ignored
 */
void cwd_tish(char **args);

/**
 * @brief Prints information about tish (NOT FULLY IMPLEMENTED)
 * 
 * @param args Arguments: Ignored
 */
void ver_tish(char **args);

/**
 * @brief Launches a built-in command
 * 
 * @param name Command entered in CLI
 * @param args Argument/s
 * @return int 0 if successfuly, 1 if failed
 */
int execTishCommand(char* name, char **args);

#endif