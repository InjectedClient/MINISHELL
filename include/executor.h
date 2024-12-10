#ifndef EXECUTOR_H
# define EXECUTOR_H

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main
char    *get_path_from_env(char *name, char *envp[]);
char    *get_cmd_path(char *cmd, char *envp[]);
void    exec(char *cmd[], char *envp[]);

char	**ft_split(char const *s, char c);

// Utils 1
int	ft_strncmp(const char *first, const char *second, size_t length);
int	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// Utils 2
void free_array(char **array);

// Error
void exit_with_error(const char *message, int exit_code);
void free_tab_and_exit(char **ptr);
void *malloc_check(void *ptr);

void get_input(int argc, char **argv, char *envp[]);

#endif