#include "../../../include/minishell.h"

t_env *create_env_node(char *env_var)
{
    t_env *new_node = malloc(sizeof(t_env));
    char    *equal_sign = ft_strchr(env_var, '=');
    
    if (!new_node || !equal_sign)
        return (NULL);
    new_node->name = ft_strndup(env_var, equal_sign - env_var);
    new_node->value = ft_strdup(equal_sign + 1);
    new_node->next = NULL;
    return (new_node);
}

t_env *init_env_list(char **envp)
{
    int i;

    t_env   *head = NULL;
    t_env   *current = NULL;
    t_env   *new_node = NULL;

    i = 0;
    while (envp[i])
    {
        new_node = create_env_node(envp[i]);
        if (!new_node)
            continue;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }
    return (head);
}

