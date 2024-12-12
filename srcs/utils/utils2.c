#include "../../include/minishell.h"

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
