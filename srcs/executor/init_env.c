/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:28:51 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/10 15:29:04 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_env_node(t_env *node)
{
    if (!node)
        return;
    if (node->name)
        free(node->name);
    if (node->value)
        free(node->value);
    free(node);
}

void free_env_list(t_env *head)
{
    t_env *tmp;

    while (head)
    {
        tmp = head->next;   // Sauvegarde le nœud suivant
        free(head->name);   // Libère le nom
        free(head->value);  // Libère la valeur
        free(head);         // Libère le nœud lui-même
        head = tmp;         // Passe au nœud suivant
    }
}


t_env *create_env_node(char *env_var)
{
    t_env *new_node;
    char *equal_sign;

    equal_sign = ft_strchr(env_var, '=');
    if (!equal_sign)
        return (NULL); // Pas de '=' dans la variable d'environnement

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL); // Erreur d'allocation

    new_node->name = ft_strndup(env_var, equal_sign - env_var);
    new_node->value = ft_strdup(equal_sign + 1);
    new_node->next = NULL;

    if (!new_node->name || !new_node->value)
    {
        free_env_node(new_node); // Libère tout en cas d'échec
        return (NULL);
    }
    return (new_node);
}


t_env *init_env_list(char **envp)
{
    int i;
    t_env   *head;
    t_env   *current;
    t_env   *new_node;

    head = NULL;
    new_node = NULL;
    i = 0;
    while (envp[i])
    {
        new_node = create_env_node(envp[i]);
        if (new_node)
        {
            if (!head)
                head = new_node;
            else
                current->next = new_node;
            current = new_node;
        }
        i++;
    }
    return (head);
}
