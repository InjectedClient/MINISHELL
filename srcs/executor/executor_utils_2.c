/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:52:36 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/23 17:00:55 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_with_error(t_lexer **commands, int num_commands)
{
	free_commands(commands, num_commands);
	return (1);
}

void	child_process_1(t_data *data, int i, int **pipes, int files[2])
{
	int	num_commands;
	t_lexer	**commands;

	commands = data->commands;
	num_commands = data->num_commands;
	if (handle_redirections(commands[i], &files[0], &files[1]))
		exit(exit_with_error(commands, num_commands));
	if (i > 0 && files[0] == -1)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_commands - 1 && files[1] == -1)
		dup2(pipes[i][1], STDOUT_FILENO);
	free_pipes(num_commands, pipes);
}

void	child_process_2(char **envp, int files[2], int i, t_data *data)
{
	char	**args;
	t_lexer	**commands;

	commands = data->commands;
	args = split_args(commands[i]);
	if (is_builtin(args[0]))
	{
		g_global = exec_builtins_with_redirections(args, data->env_list,
				files[0], files[1]);
		exit(g_global);
	}
	exec(args, data->env_list, envp);
	free_tab(args);
	perror("exec");
	exit(127);
}

void	free_commands_pipes(t_data *data, int **pipes)
{
	free_pipes(data->num_commands, pipes);
	free_commands(data->commands, data->num_commands);
}

int	init_commands(t_data *data)
{
	data->commands = split_by_pipe(data->lexer_list);
	if (!data->commands)
		return (0);
	return (1);
}
