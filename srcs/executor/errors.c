#include "../../include/minishell.h"

void exit_with_error(const char *message, int exit_code)
{
    perror(message);
    exit(exit_code);
}


void free_tab_and_exit(char **ptr)
{
    free_array(ptr);
    perror("Malloc error");
    exit(EXIT_FAILURE);
}


void *malloc_check(void *ptr)
{
    if (!ptr)
    {
        perror("Malloc error");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}
