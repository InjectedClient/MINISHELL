#include "../../include/minishell.h"

int error()
{
    perror("error_general");
    return (1);    
}

int malloc_error()
{
    perror("malloc");
    return (1);
}

int fork_error()
{
    perror("fork");
    return(1);
}

int cmd_not_exec()
{
    perror("command_not_executable");
    return (126);
}

int cmd_not_found()
{
    perror("command_not_found");
    return (127);
}
