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


#define SPACE_CHAR          ' '
#define QMARK_CHAR          '\"'
#define BSLASH_CHAR         '\\'
#define VBAR_CHAR           '|'
#define GT_CHAR             '>'
#define AOUTREDIR_CHAR      '>>'
#define LT_CHAR             '<'
#define SCOLON_CHAR         ';'
#define NULL_CHAR           '\0'

/**
 * @brief Special characters which are considered to be invalid
 *        characters if used improperly in tish
 * 
 */
const char specialTishChars[] = {'~', '`', '#', '$', '&', '*',
                                 '(', ')', '[', ']', '{', '}',
                                 ':', '=', '?', '/', '!', '@',
                                 '\'', QMARK_CHAR, BSLASH_CHAR,
                                 VBAR_CHAR, GT_CHAR, LT_CHAR,
                                 SCOLON_CHAR};

/**
 * @brief Tokenises the input made by the user
 * 
 * @param inputBuffer   Input made by the user
 * @return char*        Arguments present in input
 */
char* tokenizer(char* inputBuffer);

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

#endif