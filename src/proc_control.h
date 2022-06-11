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

#endif