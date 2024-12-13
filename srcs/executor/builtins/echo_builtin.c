#include "../../../include/minishell.h"

int    builtin_echo(char **args)
{
    int i;
    int newline;

    newline = 1;
    i = 1;
    if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}
