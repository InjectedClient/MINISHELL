#include "../../include/minishell.h"

char    *expander(char *str)
{
    char    *value;

    if (!str)
        return (ft_strdup(""));
    value = getenv(str);
    if (value)
        return (ft_strdup(value));
    return (ft_strdup(""));
}
