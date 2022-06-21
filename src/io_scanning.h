/**
 * @file terminal_io.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Terminal Input and Output and Advanced Scanning (Tasks 3 & 4)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __IO_SCANNING_H
#define __IO_SCANNING_H

#define GT_CHAR             '>'
#define LT_CHAR             '<'
#define VBAR_CHAR           '|'
#define SPACE_CHAR          ' '
#define QMARK_CHAR          '\"'
#define BSLASH_CHAR         '\\'
#define SCOLON_CHAR         ';'

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
 * @brief Get the length of string "object"
 * 
 * @param str String to get length from
 * @return int length of string
 */
int get_str_length(string_t* str);

/**
 * @brief Output the string "object"
 * 
 * @param str String to output
 */
void print_str(string_t* str);

/**
 * @brief Free memory allocated to string
 * 
 * @param str String to free memory allocated to it
 */
void free_str(string_t* str);

/**
 * @brief Initialise the argument composite data type
 * 
 * @return arg_t initialised, memory allocated argument
 */
arg_t* init_arg();

/**
 * @brief Output the argument "object"
 * 
 * @param arg Argument to output
 */
void print_arg(arg_t* arg);

/**
 * @brief Free memory allocated to argument
 * 
 * @param arg Argument to free memory allocated to it
 */
void free_args(arg_t* arg);

#endif