#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h> // Pour exit, EXIT_FAILURE, EXIT_SUCCESS
#include <stdio.h>  // Pour perror
#include "utils.h"

// Error
void exit_with_error(const char *message, int exit_code);
void free_tab_and_exit(char **ptr);
void *malloc_check(void *ptr);

int execve_error();
int fork_error();

#endif