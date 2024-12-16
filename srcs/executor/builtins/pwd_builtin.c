#include "../../../include/minishell.h"

int builtin_pwd()
{
    char    cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("minishell: pwd");
        return (1);
    }
    printf("%s\n", cwd);
    return (0);
}