/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:09 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 11:09:33 by nlambert         ###   ########.fr       */
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

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strndup(const char *source, size_t size)
{
	char	*copy;

	if (source == NULL)
		return (NULL);
	copy = malloc(sizeof(char) * (size + 1));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, source, size + 1);
	return (copy);
}

char	*ft_strchr(const char *str, int searchedChar)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == searchedChar)
			return ((char *)str);
		str++;
	}
	if (searchedChar == '\0')
		return ((char *)str);
	return (NULL);
}
