#include "../include/minishell.h"

int	count_commands(t_lexer *lexer_list)
{
	int	count;
	t_lexer	*current;

	count = 1;
	current = lexer_list;
	while (current)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void free_lexer_list(t_lexer *list)
{
    t_lexer *temp;

    while (list)
    {
        temp = list->next;
        free(list->cmd_segment);
        free(list);
        list = temp;
    }
}

void free_commands(t_lexer **commands, int num_commands)
{
    int i;

    i = 0;
    if (!commands)
        return;
    while (i < num_commands)
    {
        if (commands[i])
            free_lexer_list(commands[i]);
		i++;
    }
    free(commands);
}

void close_pipes(int num_commands, int pipes[][2])
{
	int i;

	i = 0;
    while (i < num_commands - 1)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
}