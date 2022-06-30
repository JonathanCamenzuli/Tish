/**
 * @file tfetch.h
 * @author Jonathan Camenzuli
 * @brief 
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TFETCH_H
#define __TFETCH_H

#define GREEN_ANSI          "\e[0;32m"
#define RESET_ANSI          "\e[0m"

#define LOGO_ROWS           9
#define LOGO_COLS           40

#define TF_STR_BUFFER_LEN   512

/**
 * @brief Array containing the logo displayed in tfetch
 *     
 */
extern char asciiTishLogo[LOGO_ROWS][LOGO_COLS];

/**
 * @brief Gets the tfetch title
 * 
 * @param tfetchTitle Pointer to store the title itself
 */
void getTfetchTitle(char* tfetchTitle);

/**
 * @brief Gets the lines under the tfetch title
 * 
 * @param lines Pointer to store the line itself
 */
void getLineUnderTitle(char* lines);

/**
 * @brief Gets the operating system of the host system
 * 
 * @param osStr Pointer to store the OS itself
 */
void getOS(char* osStr);

/**
 * @brief Get the kernel of the host system
 * 
 * @param kernelStr Pointer to store the Kernel itself
 */
void getKernel(char* kernelStr);

/**
 * @brief Get the shell currently being used
 * 
 * @param kernelStr Pointer to store the shell itself
 */
void getShell(char* shellStr);

/**
 * @brief Main function to be called
 * 
 */
void tfetch(void);

#endif