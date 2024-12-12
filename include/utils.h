#include <stdlib.h> // malloc, free

// Utils 1
int	ft_strncmp(const char *first, const char *second, size_t length);
int	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// Utils 2
void free_array(char **array);
int	ft_white_space(char c);
char	*ft_strdup(const char *source);

char	**ft_split(char const *s, char c);