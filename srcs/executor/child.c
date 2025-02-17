/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:14:56 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:14:57 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wait_for_children(pid_t *pids, int num_commands)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	return (last_status);
}

void	child_process(t_data *data, int **pipes, int i, t_env *env_list)
{
	int		files[2];
	t_lexer	*command;
	char	**args;

	command = data->commands[i];
	args = split_args(command);
	if (handle_redirections(command, &files[0], &files[1]))
		exit (1);
	if (i > 0 && files[0] == -1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	if (i < data->num_commands - 1 && files[1] == -1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	close_pipes(pipes, data->num_commands);
	exec(args, env_list);
	free_array(args);
	exit (1);
}
