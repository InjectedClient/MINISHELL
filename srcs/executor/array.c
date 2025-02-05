/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:14:42 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/04 14:02:19 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	len_list(t_env *list)
{
	size_t	len;
	t_env	*current;

	len = 0;
	current = list;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

char	*concat_env_var(t_env *current, char **array, int i)
{
	char	*temp;

	temp = ft_strjoin(current->name, "=");
	if (!temp)
	{
		free_array(array);
		return (NULL);
	}
	if (current->value)
	{
		array[i] = ft_strjoin(temp, current->value);
		free(temp);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
	}
	else
		array[i] = temp;
	return (array[i]);
}

char	**list_to_array(t_env *env)
{
	int		i;
	char	**array;
	t_env	*current;

	i = 0;
	current = env;
	array = malloc(sizeof(char *) * (len_list(env) + 1));
	if (!array)
		return (NULL);
	while (current)
	{
		if (!concat_env_var(current, array, i))
			return (NULL);
		i++;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}
