/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:53:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/23 14:53:03 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	**split_by_pipe(t_lexer *lexer_list)
{
	int		index;
	t_lexer	**commands;
	t_lexer	*current;
	t_lexer	*start;

	commands = malloc(sizeof(t_lexer *) * (count_commands(lexer_list)));
	if (!commands)
		return (NULL);
	index = 0;
	start = lexer_list;
	current = lexer_list;
	while (current)
	{
		if (current->token == PIPE)
		{
			current->prev->next = NULL;
			current->prev = NULL;
			commands[index++] = start;
			start = current->next;
		}
		current = current->next;
	}
	commands[index] = start;
	return (commands);
}

int	 create_pipes(t_data *data, int **pipes)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i-- > 0)
			{
				free(pipes[i]);
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			free(pipes);
			return (0);
		}
		i++;
	}
	return (1);
}

int	execute_builtins_without_pipes(t_data *data, int i, int files[2])
{
	char	**args;
	int		num_commands;
	t_lexer	**commands;

	commands = data->commands;
	num_commands = count_commands_from_array(commands);
	args = split_args(commands[i]);
	if (handle_redirections(commands[i], &files[0], &files[1]))
	{
		free_commands(commands, num_commands);
		free_tab(args);
		exit(1);
	}
	g_global = exec_builtins_with_redirections(args, data->env_list,
			files[0], files[1]);
	free_tab(args);
	return (g_global);
}

int	pid_error(t_lexer **commands, int num_commands)
{
	perror("fork");
	free_commands(commands, num_commands);
	return (1);
}

int	count_commands_from_array(t_lexer **commands)
{
	int	count;

	count = 0;
	if (!commands)
		return (0);
	while (commands[count])
		count++;
	return (count);
}
