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

size_t	ft_strlen_until(const char *str, const char *stop_chars)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str || !stop_chars)
		return (0);
	while (str[i])
	{
		j = 0;
		while (stop_chars[j])
		{
			if (str[i] == stop_chars[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
