/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 15:53:13 by nlambert         ###   ########.fr       */
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

int	execute_token(t_lexer *lexer_list, t_env *env_list,
		char **envp, int num_commands)
{
	int		i;
	int		**pipes;
	pid_t	pid;
	t_lexer	**commands;
	int		files[2];

	pipes = malloc(sizeof(int *) * (num_commands - 1));
	if (!pipes)
		return (1);
	commands = NULL;
	if (start_execute_token(lexer_list, num_commands, pipes, &commands) == 1)
		return (1);
	i = -1;
	while (++i < num_commands)
	{
		if (is_builtin(commands[0]->cmd_segment)
			&& num_commands == 1 && commands[i]->token != PIPE)
			return (execute_builtins_without_pipes(env_list,
					commands, i, files));
		pid = fork();
		if (pid == -1)
			pid_error(commands, num_commands);
		if (pid == 0)
		{
			child_process_1(commands, i, num_commands, pipes, files);
			child_process_2(env_list, envp, files, i, commands);
		}
	}
	end_execute_token(commands, num_commands, pipes);
	return (0);
}
