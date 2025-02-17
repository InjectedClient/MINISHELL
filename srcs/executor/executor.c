/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/10 14:03:42 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(char *cmd[], t_env *env_list)
{
	if (is_builtin(cmd[0]))
		exit (exec_builtins(cmd, env_list));
	else
		exec_cmd_with_fork(cmd, env_list);
}

int	execute_commands(t_data *data, int **pipes, pid_t *pids, t_env *env_list)
{
	int		i;
	int		status;

	i = -1;
	while (++i < data->num_commands)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("minishell");
			return (0);
		}
		if (pids[i] == 0)
			child_process(data, pipes, i, env_list);
	}
	close_pipes(pipes, data->num_commands);
	status = wait_for_children(pids, data->num_commands);
	return (status);
}

int	execute_token(t_data *data, t_env *env_list)
{
	int		status;
	int		**pipes;
	pid_t	*pids;

	pipes = NULL;
	pids = NULL;
	status = 0;
	if (data->num_commands == 1)
		return (handle_cmd_without_pipe(data, env_list));
	if (create_pids(data, &pids) == 0 || create_pipes(data, &pipes) == 0)
	{
		free_pids(&pids);
		free_pipes(data->num_commands, &pipes);
		return (1);
	}
	status = execute_commands(data, pipes, pids, env_list);
	free_pids(&pids);
	free_pipes(data->num_commands, &pipes);
	return (status);
}

