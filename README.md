```
                                     /$$     /$$           /$$      
                                    | $$    |__/          | $$      
                                   /$$$$$$   /$$  /$$$$$$$| $$$$$$$ 
                                  |_  $$_/  | $$ /$$_____/| $$__  $$
                                    | $$    | $$|  $$$$$$ | $$  \ $$
                                    | $$ /$$| $$ \____  $$| $$  | $$
                                    |  $$$$/| $$ /$$$$$$$/| $$  | $$
                                     \___/  |__/|_______/ |__/  |__/   v1.0
```
# Introduction
Tiny SHell (`tish`) is a small, basic and inefficient (Yes, I said inefficient) Unix shell.
# Structure
Basecode is structured as follows:
- *repo*
  - *build*
  - *libs*
  - *src*
  - *testing*
  - `CMakeLists.txt`

## *build*
Contains the executable file `tish` and other files which were used in the compostion of said executable with CMake

## *libs*
Contains the source files which are not necessarily mentioned in the assignment specifications but are used in the assigment

## *src*
Contains the source files which contain the code that is required by the assignment specifications.

## *testing*
This directory was used in the testing stage of the project.

## `CMakeLists.txt`
Contains the configuration used to build the executable file in CMake.

# Compilation
The executable is available in *`./build/tish`* however, for all intents and purposes, it can produced with the following command, given that the cwd is the root:  *`(cd build && make)`*

Otherwise, if the cwd is *build*, the *`make`* command on its own will suffice. Please note that both build methods require CMake.

# Known Issues

- Segmentation fault caused when performing unmatched quotes test
- When using multiple redirection tokens in one command, it would fail to do what is intended to do


# To-do List
- [x] Implementing `tfetch`
- [x] Testing: Command Pipelines
- [x] Testing: Advanced Scanning
- [x] Testing: Error Handling
- [x] Testing: Built-in Commands
