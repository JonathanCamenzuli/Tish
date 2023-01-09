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

Tiny SHell (`tish`) is a small, basic and inefficient (yes, you read that right) Unix shell.

# Structure

Basecode is structured as follows:

- _repo_
  - _build_
  - _libs_
  - _src_
  - _testing_
  - `CMakeLists.txt`

## _build_

Contains the executable file `tish` and other files which were used in the compostion of said executable with CMake

## _libs_

Contains the source files which are not necessarily mentioned in the assignment specifications but are used in the assigment

## _src_

Contains the source files which contain the code that is required by the assignment specifications.

## _testing_

This directory was used in the testing stage of the project.

## `CMakeLists.txt`

Contains the configuration used to build the executable file in CMake.

# Compilation

The executable is available in _`./build/tish`_ however, for all intents and purposes, it can produced with the following command, given that the cwd is the root: _`(cd build && make)`_

Otherwise, if the cwd is _build_, the _`make`_ command on its own will suffice. Please note that both build methods require CMake.

# Known Issues

- Segmentation fault caused when performing unmatched quotes test
- When using multiple redirection tokens in one command, it would fail to do what is intended to do

# To-do List

- [x] Implementing `tfetch`
- [x] Testing: Command Pipelines
- [x] Testing: Advanced Scanning
- [x] Testing: Error Handling
- [x] Testing: Built-in Commands
