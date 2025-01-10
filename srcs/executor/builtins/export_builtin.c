/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:18:51 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/10 14:34:53 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_sorted_env(t_env *env_list)
{
	t_env		*current;

	current = env_list;
	while (current)
	{
		write(1, "declare -x ", 11);
		write(1, current->name, ft_strlen(current->name));
		if (current->value)
		{
			write(1, "=\"", 2);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		current = current->next;
	}
}

void	add_env_variable(t_env **env_list, char *name, char *value, int equal)
{
	t_env	*new_node;
	t_env	*current;

	current = *env_list;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free_2(name, value);
		return ;
	}
	new_node->name = ft_strdup(name);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->equal_sign = equal;
	if (!new_node->name || (value && !new_node->value))
	{
		free_2(name, value);
		free_env_node(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!current)
		*env_list = new_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
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
	}
	else
		name = ft_strdup(arg);
	if (!name || (*(equal_sign + 1) && !value))
	{
		free_2(name, value);
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free_2(name, value);
			return ;
		}
		current = current->next;
	}
	add_env_variable(env_list, name, value, equal);
}

int	is_valid_env_format(char *arg)
{
	int		i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
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
		}
		i++;
	}
	return (0);
}
