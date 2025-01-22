/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:15:11 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/22 14:15:12 by nlambert         ###   ########.fr       */
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

int	create_pipes(int num_commands, int pipes[][2])
{
	int	i;
	int	j;

	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (j < i)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	execute_builtins_without_pipes(t_env *env_list,
		t_lexer **commands, int i, int files[2])
{
	char	**args;
	int		num_commands;

	num_commands = count_commands_from_array(commands);
	args = split_args(commands[i]);
	if (handle_redirections(commands[i], &files[0], &files[1]))
	{
		free_commands(commands, num_commands);
		free_tab(args);
		exit(1);
	}
	g_global = exec_builtins_with_redirections(args, env_list,
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
