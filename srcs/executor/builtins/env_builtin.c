#include "../../../include/minishell.h"

int    builtin_env(t_env *env_list)
{
    t_env *current;

    current = env_list;
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->name, current->value);
        if (current->equal_sign && !current->value)
            printf("%s=\n", current->name);
        current = current->next;
    }
    return (0);
}
