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
#define BLUE_ANSI           "\e[0;34m"
#define RED_ANSI            "\e[0;31m"			
#define RESET_ANSI          "\e[0m"

#define TF_STR_BUFFER_LEN   512

extern const char ansiTishLogo[8][40];

void getTfetchTitle(char* tfetchTitle);

void getLinesUnderTitle(char* lines);

void getOS(char* osStr);

void getKernel(char* kernelStr);

void getShell(char* shellStr);

void getColors(char* colours);

void tfetch(void);

#endif