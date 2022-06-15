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

#endif