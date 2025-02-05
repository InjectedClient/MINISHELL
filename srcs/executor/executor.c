/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 15:25:02 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec(char *cmd[], t_data *data)
{
	if (is_builtin(cmd[0]))
		exit (exec_builtins(cmd, data));
	else
		exec_cmd_with_fork(cmd, data->env_list);
}

int	execute_commands(t_data *data, int **pipes, pid_t *pids)
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
			child_process(data, pipes, i);
	}
	close_pipes(pipes, data->num_commands);
	status = wait_for_children(pids, data->num_commands);
	return (status);
}

int	execute_token(t_data *data)
{
	int		status;
	int		**pipes;
	pid_t	*pids;

	pipes = NULL;
	pids = NULL;
	status = 0;
	if (data->num_commands == 1)
		return (handle_cmd_without_pipe(data));
	if (init_commands(data) == 0 || create_pids(data, &pids) == 0
		|| create_pipes(data, &pipes) == 0)
	{
		free_pids(&pids);
		free_pipes(data->num_commands, &pipes);
		free_commands(&data->commands, data->num_commands);
		return (1);
	}
	status = execute_commands(data, pipes, pids);
	free_pids(&pids);
	free_pipes(data->num_commands, &pipes);
	free_commands(&data->commands, data->num_commands);
	return (status);
}

void	free_data(t_data *data)
{
	if (!data->args)
		return ;
	if (data->lexer_list)
		free_lexer_list(data->lexer_list);
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->input_cmd)
		free(data->input_cmd);
}
