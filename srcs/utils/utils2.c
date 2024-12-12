#include "utils.h"

# define SHIFT_OUT 14 // SO (Shift Out)

void free_array(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

int	ft_white_space(char c)
{
	return (c == ' ' || (c > '\b' && c < SHIFT_OUT));
}

char	*ft_strdup(const char *source)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(source);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, source, len + 1);
	return (copy);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	src_len = ft_strlen(src);
	if (size > 0)
	{
		dst_len = 0;
		while (dst_len < size - 1 && src[dst_len])
		{
			dst[dst_len] = src[dst_len];
			dst_len++;
		}
		dst[dst_len] = '\0';
	}
	return (src_len);
}
