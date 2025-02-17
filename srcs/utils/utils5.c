/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:08:29 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/17 17:44:24 by nlambert         ###   ########.fr       */
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

void	free_lexer_list2(t_lexer *lexer_list)
{
	t_lexer	*tmp;

	while (lexer_list)
	{
		tmp = lexer_list;
		lexer_list = lexer_list->next;
		if (tmp->cmd_segment)
			free(tmp->cmd_segment);
	}
}

int	rm_space(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	while (len > 0 && str[len - 1] == ' ')
	{
		str[len - 1] = '\0';
		len--;
	}
	return (1);
}