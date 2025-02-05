/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_without_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:15:05 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/04 14:02:52 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd_with_fork(char **cmd, t_env *env_list)
{
	char	*path;
	char	**envp;

	envp = list_to_array(env_list);
	if (!envp)
		exit (1);
	if (execve(cmd[0], cmd, envp) == -1)
	{
		path = get_cmd_path(cmd[0], env_list);
		if (!path)
		{
			write(2, "minishell: ", 11);
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 20);
			exit (127);
		}
		if (execve(path, cmd, envp) == -1)
		{
			perror("minishell ");
			free(path);
			exit (127);
		}
		free(path);
	}
	exit (1);
}

int	exec_cmd_without_pipe(char **cmd, t_data *data)
{
	int		status;
	pid_t	pid;

	if (is_builtin(cmd[0]))
		return (exec_builtins(cmd, data));
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_cmd_with_fork(cmd, data->env_list);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	handle_cmd_without_pipe(t_data *data)
{
	int		files[2];
	int		stdin_stdout[2];
	int		status;
	char	**args;
	t_lexer	*command;

	if (init_saved_fds(&stdin_stdout[0], &stdin_stdout[1]))
		return (1);
	command = data->lexer_list;
	if (handle_redirections(command, &files[0], &files[1]))
	{
		restore_and_close_saved_fds(stdin_stdout[0], stdin_stdout[1]);
		return (1);
	}
	args = split_args(command);
	if (!args)
	{
		restore_and_close_saved_fds(stdin_stdout[0], stdin_stdout[1]);
		return (1);
	}
	status = exec_cmd_without_pipe(args, data);
	free_array(args);
	if (restore_and_close_saved_fds(stdin_stdout[0], stdin_stdout[1]))
		return (1);
	return (status);
}
