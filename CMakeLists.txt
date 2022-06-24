cmake_minimum_required(VERSION 3.15)
project(tish-project C)

add_executable(tish libs/linenoise.c src/tish.c src/io_scanning.c src/commands.c src/proc_control.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})