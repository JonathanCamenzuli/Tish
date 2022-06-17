/**
 * @file proc_control.h
 * @author Jonathan Camenzuli
 * @brief CPS1012 Assignment - Process Control (Task 1)
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PROC_CONTROL_H
#define __PROC_CONTROL_H

/**
 * @brief Launches an executable using the fork-exec pattern.
 * 
 * @param pipelineArgs  Arguments
 * @param fileIn        Specify file input used for redirection
 * @param fileOut       Specify file output used for redirection
 * @param appendOut     If true, output to file is appended, else it's truncated
 * @param asyncEnable   If true, program terminates without waiting for pipeline to terminate 
 * @return int 
 */
int forkExecPipe(char ***pipelineArgs[], char *fileIn, char *fileOut, bool appendOut, bool asyncEnable);

/**
 * @brief Works like freopen() from stdio.h but uses file descriptors instead
 * 
 * @param fd        File descriptor
 * @param pathName  Path of file to open
 * @param flags     Method of which the file is to be opened
 * @param mode      Determines permissions of file (if created)
 * @return int      File descriptor or its duplicate
 */
int reopen(int fd, char* pathName, int flags, unsigned int mode);

/**
 * @brief Sets up redirection for file input 
 * 
 * @param input File input
 * @return int  File descriptor or its duplicate
 */
int redirectInput(char* input);

/**
 * @brief Sets up redirection for file output
 * 
 * @param output        File output
 * @param appendFlag    Method of which the file is to be opened
 * @return int          File descriptor or its duplicate
 */
int redirectOutput(char* output, int appendFlag);

#endif