#include "../../../include/minishell.h"

#include <limits.h> // Pour LONG_MAX et LONG_MIN

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

long ft_atol(const char *str)
{
    long result = 0;
    int sign = 1;

    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str && ft_isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        if (result < 0) // Gestion simple de débordement
            return (sign == 1 ? LONG_MAX : LONG_MIN);
        str++;
    }
    return (result * sign);
}

int builtin_exit(char **args)
{
    long exit_code;

    printf("exit\n");
    if (!args[1]) // Aucun argument
        exit(0);
    if (is_numeric(args[1]))
    {
        exit_code = ft_atol(args[1]);
        if (exit_code < 0 || exit_code > 255) // Code de sortie limité à 8 bits
            exit_code = (unsigned char)exit_code;
        if (args[2]) // Trop d'arguments
        {
            write(2, "minishell: exit: too many arguments\n", 36);
            return (1); // Ne quitte pas le shell parent
        }

        exit(exit_code); // Quitte avec le code donné
    }
    else
    {
        // Argument non numérique
        write(2, "minishell: exit: ", 17);
        write(2, args[1], ft_strlen(args[1]));
        write(2, ": numeric argument required\n", 28);
        exit(2); 
    }

    return (0); // Ne devrait jamais atteindre ce point
}
