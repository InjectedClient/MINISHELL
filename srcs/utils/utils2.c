#include "../../include/minishell.h"

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

void	exit_all(t_data *data)
{
	ft_write_fd("exit\n", 1);
	ft_free_all(data);
	exit(0);
}

void	ft_free_all(t_data *data)
{
	t_free_memory	*tmp;
	t_free_memory	*next;

	tmp = data->free_memory;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->add)
			free(tmp->add);
		free(tmp);
		tmp = next;
	}
}
int	ft_write_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (write (fd, str, i) == -1)
	{
		printf("write error: no space left on device\n");
		g_global = 1;
		return (1);
	}
	return (0);
}
