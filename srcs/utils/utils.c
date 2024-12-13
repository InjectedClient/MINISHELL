#include "../include/minishell.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	if (!first || !second)
		return (-1);
	while (length > 0 && (*first || *second))
	{
		if (*first != *second)
			return ((unsigned char)*first - (unsigned char)*second);
		first++;
		second++;
		length--;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	const char *ptr = str;

	if (!str)
		return (0);
	while (*ptr)
		ptr++;
	return (ptr - str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2 + 1;
	result = malloc(total_len * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	ft_strlcat(result, s2, total_len);
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	max_append_len;

	if (!dst || !src)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	max_append_len = size - dst_len - 1;
	i = 0;
	while (i < max_append_len && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
