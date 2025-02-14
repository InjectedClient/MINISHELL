/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:09 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/14 15:24:15 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
