#include "../../../include/minishell.h"

int    builtin_env(char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (1);
}
