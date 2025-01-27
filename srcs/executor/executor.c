/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/23 17:54:09 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmd_2(char **cmd, char *envp[], t_env *env_list)
{
	char	*path;

	if (execve(cmd[0], cmd, envp) == -1)
	{
		path = get_cmd_path(cmd[0], env_list);
		if (!path)
			return (cmd_not_found());
		if (execve(path, cmd, envp) == -1)
			return (cmd_not_exec());
	}
	return (0);
}

void	exec(char *cmd[], t_env *env_list, char **envp)
{
	if (is_builtin(cmd[0]))
		g_global = exec_builtins(cmd, env_list);
	else
		g_global = exec_cmd_2(cmd, envp, env_list);
}

int	execute_commands(t_data *data, char **envp, int **pipes, int *files)
{
	int		i;
	t_lexer	**commands;
	pid_t	pid;

	commands = data->commands;
	i = -1;
	while (++i < data->num_commands)
	{
		if (is_builtin(commands[0]->cmd_segment) && \
		data->num_commands == 1 && commands[i]->token != PIPE)
		{
			execute_builtins_without_pipes(data, i, files);
			return (1);
		}
		pid = fork();
		if (pid == -1)
			pid_error(commands, data->num_commands);
		if (pid == 0)
		{
			child_process_1(data, i, pipes, files);
			child_process_2(envp, files, i, data);
		}
	}
	return (0);
}

int	execute_token(t_data *data, char **envp)
{
	int		**pipes;
	int		files[2];

	pipes = malloc(sizeof(int *) * (data->num_commands - 1));
	if (!pipes)
		return (1);
	if (!create_pipes(data, pipes))
		return (1);
	if (!init_commands(data))
	{
		free_pipes(data->num_commands, pipes);
		return (1);
	}
	if (execute_commands(data, envp, pipes, files))
	{
		free_commands_pipes(data, pipes);
		return (g_global);
	}
	free_pipes(data->num_commands, pipes);
	wait_for_children(data->num_commands);
	free_commands(data->commands, data->num_commands);
	return (0);
}

void	free_data(t_data *data)
{
	if (!data->args)
		return ;
	if (data->args)
		free_tab(data->args);
	if (data->lexer_list)
		free_lexer_list(data->lexer_list);
	if (data->env_list)
		free_env_list(data->env_list);
	if (data->input_cmd)
		free(data->input_cmd);
	free(data);
}
