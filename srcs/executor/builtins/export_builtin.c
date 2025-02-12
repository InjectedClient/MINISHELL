/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:18:51 by jle-neze          #+#    #+#             */
/*   Updated: 2025/02/12 16:47:30 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*create_env_node2(char *name, char *value, int equal)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free_3_env(new_node->name, NULL, new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->equal_sign = equal;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_variable(t_env **env_list, char *name, char *value, int equal)
{
	t_env	*new_node;

	new_node = create_env_node2(name, value, equal);
	if (!new_node)
		return ;
	add_new_node(new_node, env_list);
}

int	update_env(t_env *current, char *name, char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (0);
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				free(current->value);
			current->value = new_value;
			return (1);
		}
		current = current->next;
	}
	free(new_value);
	return (0);
}

void	update_or_add_env(t_env **env_list, char *arg)
{
	int		equal;
	char	*equal_sign;
	char	*name;
	char	*value;
	t_env	*current;

	equal = 0;
	current = *env_list;
	value = NULL;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		equal = 1;
		name = ft_substr(arg, 0, equal_sign - arg);
		if (*(equal_sign + 1) != '\0')
			value = ft_strdup(equal_sign + 1);
		else
			value = ft_strdup("");
	}
	else
		name = ft_strdup(arg);
	if (!update_env(current, name, value))
		add_env_variable(env_list, name, value, equal);
	free_2(name, value);
}

int	builtin_export(char **args, t_env **env_list)
{
	int		i;

	if (!env_list || !*env_list)
		return (1);
	if (!args[1])
	{
		print_sorted_env(*env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (is_valid_env_format(args[i]))
			update_or_add_env(env_list, args[i]);
		else
		{
			write(2, "minishell: ", 11);
			write(2, "export: `", 9);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "`: not a valid identifier\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}
