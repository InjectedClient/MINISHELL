/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:09 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/18 15:49:59 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_to_free_memory(t_data *data, void *add)
{
	t_free_memory	*mem;
	t_free_memory	*tmp;

	mem = malloc(sizeof(t_free_memory));
	if (!mem)
		return ;
	mem->add = add;
	mem->next = NULL;
	if (data->free_memory == NULL)
		data->free_memory = mem;
	else
	{
		tmp = data->free_memory;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mem;
	}
}

void	*malloc_track(t_data *data, size_t size)
{
	void	*add;

	add = malloc(size);
	if (!add)
		return (NULL);
	add_to_free_memory(data, add);
	return (add);
}