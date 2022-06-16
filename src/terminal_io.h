/**
 * @file terminal_io.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Terminal Input and Output (Task 3)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TERMINAL_IO_H
#define __TERMINAL_IO_H

/**
 * @brief A struct that represents a string
 * 
 */
typedef struct 
{
    char *string;   /**< the string itself */
    int size;       /**< the size of string itself */
}string_t;

/**
 * @brief A struct that represents an argument
 * 
 */
typedef struct
{
    char **args;    /**< the string itself */
    int size;       /**< the size of string itself */ 
}arg_t;

/**
 * @brief Initialise the string composite data type
 * 
 * @return string_t initialised, memory allocated string
 */
string_t* init_str();

/**
 * @brief Initialise the argument composite data type
 * 
 * @return arg_t initialised, memory allocated argument
 */
arg_t* init_arg();

#endif