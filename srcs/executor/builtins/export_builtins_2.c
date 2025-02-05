/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtins_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:53:33 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/04 13:59:22 by jle-neze         ###   ########.fr       */
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

void	add_new_node(t_env *new_node, t_env **env_list)
{
	t_env	*current;

	current = *env_list;
	if (!current)
		*env_list = new_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
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
