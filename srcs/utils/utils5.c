/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:08:29 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 11:10:43 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	*malloc_track(t_data *data, size_t size)
{
	void	*add;

	add = malloc(size);
	if (!add)
		return (NULL);
	add_to_trash_memory(data, add);
	return (add);
}

void	add_to_trash_memory(t_data *data, void *add)
{
	t_trash_memory	*mem;
	t_trash_memory	*tmp;

	mem = malloc(sizeof(t_trash_memory));
	if (!mem)
		return ;
	mem->add = add;
	mem->next = NULL;
	if (data->trash_memory == NULL)
		data->trash_memory = mem;
	else
	{
		tmp = data->trash_memory;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mem;
	}
}