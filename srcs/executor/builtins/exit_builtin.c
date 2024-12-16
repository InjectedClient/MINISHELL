#include "../../../include/minishell.h"

int is_numeric(const char *str)
{
    if (!str || *str == '\0')
        return (0);
    if (*str == '+' || *str == '-')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

int     builtin_exit(char **args)
{
    int exit_code;

    exit_code = 0;
    printf("exit\n");
    if (!args[1])
        exit(exit_code);
    if (is_numeric(args[1]))
    {
        exit_code = ft_atoi(args[1]);
        if (args[2])
        {
            write(2, "minishell: exit: too many arguments\n", 36);
            return (1);
        }
        exit(exit_code);
    }
    else
    {
        write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43); //essayer de rendre le truc dynamique
        exit (2);
    }
}