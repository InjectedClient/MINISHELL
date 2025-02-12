/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:08:29 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/12 17:05:46 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	init_ij(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

void	free_lexer_list(t_lexer **lexer_list)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lexer_list;
	while (current)
	{
		next = current->next;
		free(current->cmd_segment);
		free(current);
		current = next;
	}
	*lexer_list = NULL;
}
