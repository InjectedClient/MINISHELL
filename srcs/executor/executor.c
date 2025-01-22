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

void    exec(char *cmd[], t_env *env_list, char **envp)
{
    if (is_builtin(cmd[0]))
        g_global = exec_builtins(cmd, env_list);
    else
        g_global = exec_cmd_2(cmd, envp, env_list);
}

t_lexer	**split_by_pipe(t_lexer *lexer_list, int command_count)
{
	int	index;
	t_lexer	**commands;
	t_lexer	*current;
	t_lexer	*start;

	command_count = count_commands(lexer_list);
	commands = malloc(sizeof(t_lexer *) * (command_count));
	if (!commands)
	{
		perror("Allocation echouee");
		return (NULL);
	}
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

int create_pipes(int num_commands, int pipes[][2])
{
	int i;

	i = 0;
    while (i < num_commands - 1)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            for (int j = 0; j < i; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            return (1);
        }
		i++;
    }
    return (0);
}


void wait_for_children(int num_commands)
{
	int i;

	i = 0;
    while (i < num_commands)
    {
        int status;
        wait(&status);

        if (WIFEXITED(status))
        {
            if (i == num_commands - 1)
                g_global = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            g_global = 128 + WTERMSIG(status);
        }
		i++;
    }
}


int execute_token(t_lexer *lexer_list, t_env *env_list, char **envp, int num_commands)
{
	int	i;
	int	pipes[num_commands - 1][2];
	char	**args;
	pid_t	pid;
	t_lexer	**commands;
    int infile;
    int outfile;

	commands = split_by_pipe(lexer_list, num_commands);
	if (!commands)
		return (1);
	if (create_pipes(num_commands, pipes) == 1)
    {
        free_commands(commands, num_commands);
        return (1);
	}
	i = 0;
	while (i < num_commands) //faire la fonction ici
	{
        args = split_args(commands[i]);
		if (is_builtin(args[0]) && num_commands == 1 && commands[i]->token != PIPE)
		{
			if (handle_redirections(commands[i], &infile, &outfile))
			{
				free_commands(commands, num_commands);
				free_tab(args);
				exit(1);
			}
			g_global = exec_builtins_with_redirections(args, env_list, infile, outfile);
			free_tab(args);
			return (g_global);
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				free_commands(commands, num_commands);
				free_tab(args);
				return (1);
			}
			if (pid == 0) // Child
			{
				if (handle_redirections(commands[i], &infile, &outfile))
				{
					free_tab(args);
					exit(1);
				}
				if (i > 0 && infile == -1)
					dup2(pipes[i - 1][0], STDIN_FILENO);
				if (i < num_commands - 1 && outfile == -1)
					dup2(pipes[i][1], STDOUT_FILENO);
				close_pipes(num_commands, pipes);
				if (is_builtin(args[0]))
				{
					g_global = exec_builtins_with_redirections(args, env_list, infile, outfile);
					exit(g_global);
				}
				exec(args, env_list, envp);
				free_tab(args);
				perror("exec");
				exit(127);
			}
		}
		i++;
	}
    close_pipes(num_commands, pipes);
	wait_for_children(num_commands);
    free_commands(commands, num_commands);
    return (0);
}
