#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h> // Pour exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdio.h>  // Pour perror

// Error
int error();
int malloc_error();
int cmd_not_exec();
int cmd_not_found();
int fork_error();

#endif