/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/17 14:13:24 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "exit";
	builtins[4] = "pwd";
	builtins[5] = "export";
	builtins[6] = "unset";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtins(char **args, t_env *env_list)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (builtin_echo(args));
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (builtin_cd(args, &env_list));
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (builtin_export(args, &env_list));
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (builtin_unset(args, &env_list));
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (builtin_env(env_list));
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (builtin_exit(args));
	else
		return (-1);
}


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

int	count_commands(t_lexer *lexer_list)
{
	int	count;
	t_lexer	*current;

	count = 1;
	current = lexer_list;
	while (current)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return (count);
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


int handle_redirections(t_lexer *command, int *infile, int *outfile)
{
	t_lexer *current;
	int error = 0;

	*infile = -1;
	*outfile = -1;

	current = command;
	while (current)
	{
		if (current->token == REDIRECT_IN)
		{
			*infile = open(current->next->cmd_segment, O_RDONLY);
			if (*infile == -1)
			{
				perror(current->next->cmd_segment);
				error = 1;
				break;
			}
			dup2(*infile, STDIN_FILENO);
			close(*infile);
		}
		else if (current->token == REDIRECT_OUT)
		{
			*outfile = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*outfile == -1)
			{
				perror(current->next->cmd_segment);
				error = 1;
				break;
			}
			dup2(*outfile, STDOUT_FILENO);
			close(*outfile);
		}
		else if (current->token == APPEND_OUT)
		{
			*outfile = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*outfile == -1)
			{
				perror(current->next->cmd_segment);
				error = 1;
				break;
			}
			dup2(*outfile, STDOUT_FILENO);
			close(*outfile);
		}
		current = current->next;
	}

	return error; // Retourne 1 si une erreur survient, sinon 0
}

int exec_builtins_with_redirections(char **args, t_env *env_list, int infile, int outfile)
{
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);

	if (infile != -1)
		dup2(infile, STDIN_FILENO);
	if (outfile != -1)
		dup2(outfile, STDOUT_FILENO);

	int status = exec_builtins(args, env_list);

	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);

	return status;
}


int execute_token(t_data *data, t_env *env_list, char **envp, int num_commands)
{
	int	i;
	int	pipes[num_commands - 1][2];
	char	**args;
	pid_t	pid;
	t_lexer	**commands;
	t_lexer *lexer_list;
	int infile;
	int outfile;

	lexer_list = data->lexer_list;
	commands = split_by_pipe(lexer_list, num_commands);
	if (!commands)
	{
		perror("malloc error");
		return (1);
	}
	i = 0;
	for (i = 0; i < num_commands - 1; i++)
	{	
	if (pipe(pipes[i]) == -1)
	{
		perror("pipe");
		for (int j = 0; j < i; j++) // Fermer les pipes déjà créés
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
		return (1);
	}
	}



	i = 0;
	while (i < num_commands)
	{
		args = split_args(commands[i]);
		if (is_builtin(args[0]) && num_commands == 1 && commands[i]->token != PIPE)
		{
			// Exécuter directement si pas de pipe
			g_global = exec_builtins_with_redirections(args, env_list, infile, outfile);
			free_tab(args);
			return g_global; // Ne pas quitter le parent
		}
		else
		{
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return (1);
			}
			if (pid == 0) // Child
			{
				if (handle_redirections(commands[i], &infile, &outfile))
					exit(1);
				if (i > 0 && infile == -1)
				{
					dup2(pipes[i - 1][0], STDIN_FILENO);
				}
				if (i < num_commands - 1 && outfile == -1)
				{
					dup2(pipes[i][1], STDOUT_FILENO);
				}
				for (int j = 0; j < num_commands - 1; j++)
				{
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
				if (is_builtin(args[0]))
				{
					g_global = exec_builtins(args, env_list);
					exit(g_global); // Quitter avec le code de sortie du builtin
				}
				exec(args, env_list, envp);
				perror("exec");
				exit(127);
			}
		}
		i++;
	}
	// Parent : Fermer tous les pipes
	for (int i = 0; i < num_commands - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	for (int i = 0; i < num_commands; i++)
	{
		int status;
		wait(&status);

		// Mettre à jour g_global avec le code de sortie du processus enfant
		if (WIFEXITED(status)) // Si l’enfant s'est terminé normalement
		{
			g_global = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status)) // Si l’enfant s'est terminé à cause d’un signal
		{
			g_global = 128 + WTERMSIG(status);
		}
	}
	for (int i = 0; i < num_commands; i++)
	{
	free(commands[i]);
	}
	free(commands);

	return (0);
}

// int handle_redirections(t_lexer *current, int fds[2])
// {
//     if (current->token == REDIRECT_OUT)
//     {
//         fds[1] = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fds[1] == -1)
//         {
//             perror("minishell");
//             if (fds[0] != -1) // Nettoie les descripteurs précédents
//                 close(fds[0]);
//             return (-1);
//         }
//         dup2(fds[1], STDOUT_FILENO);
//         close(fds[1]);
//     }
//     else if (current->token == APPEND_OUT)
//     {
//         fds[1] = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_APPEND, 0644);
//         if (fds[1] == -1)
//         {
//             perror("minishell");
//             if (fds[0] != -1)
//                 close(fds[0]);
//             return (-1);
//         }
//         dup2(fds[1], STDOUT_FILENO);
//         close(fds[1]);
//     }
//     else if (current->token == REDIRECT_IN)
//     {
//         fds[0] = open(current->next->cmd_segment, O_RDONLY);
//         if (fds[0] == -1)
//         {
//             perror("minishell");
//             return (-1);
//         }
//         dup2(fds[0], STDIN_FILENO);
//         close(fds[0]);
//     }
//     else if (current->token == HERE_DOC)
//     {
//         fds[0] = handle_here_doc(current->next->cmd_segment);
//         if (fds[0] == -1)
//         {
//             perror("minishell");
//             return (-1);
//         }
//         dup2(fds[0], STDIN_FILENO);
//         close(fds[0]);
//     }
//     return (0);
// }


// void cleanup(int fds[2], int prev_fd, int pipe_fd[2], char **args)
// {
//     if (fds[0] != -1)
//         close(fds[0]);
//     if (fds[1] != -1)
//         close(fds[1]);
//     if (prev_fd != -1)
//         close(prev_fd);
//     if (pipe_fd[0] != -1)
//         close(pipe_fd[0]);
//     if (pipe_fd[1] != -1)
//         close(pipe_fd[1]);
//     if (args)
//         free_tab(args);
// }

// void execute_child(int fds[2], int pipe_fd[2], int prev_fd, char **args, t_env *env_list, char **envp)
// {
//     if (fds[0] != -1)
//     {
//         dup2(fds[0], STDIN_FILENO);
//         close(fds[0]);
//     }
//     else if (prev_fd != -1)
//     {
//         dup2(prev_fd, STDIN_FILENO);
//         close(prev_fd);
//     }
//     if (fds[1] != -1)
//     {
//         dup2(fds[1], STDOUT_FILENO);
//         close(fds[1]);
//     }
//     else if (pipe_fd[1] != -1)
//     {
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[1]);
//     }
//     exec(args, env_list, envp, 0);
//     perror("minishell");
//     exit(1);
// }

// int execute_token(t_data *data, t_env *env_list, char **envp)
// {
//     t_lexer *current;
//     int fds[2]; // LE 0 est in et le 1 est out 
//     int prev_fd;
//     pid_t   pid;
//     int pipe_fd[2] ={-1, -1};
//     int stdin_save = dup(STDIN_FILENO);
//     int stdout_save = dup(STDOUT_FILENO); 
//     char **args = NULL;

//     prev_fd = -1;
//     current = data->lexer_list;
//     while (current)
//     {
//         fds[0] = -1;
//         fds[1] = -1;
//         if (current->token == CMD)
//         {
//             args = split_args(current);
//             if (!args)
//                 return (1);
//         }
//         if (current->token == REDIRECT_OUT || current->token == APPEND_OUT || current->token == REDIRECT_IN || current->token == HERE_DOC)
//         {
//             if (handle_redirections(current, fds) == -1)
//             {
//                 cleanup(fds, prev_fd, pipe_fd, args);
//                 return (1);
//             }
//         }
//         if (current->token == PIPE)
//         {
//             // Créer un pipe pour la commande suivante
//             if (pipe(pipe_fd) == -1)
//             {
//                 perror("minishell");
//                 return (1);
//             }
//             printf("\n\nLa valeur de fsd[0] est %d, La valeur de fsd[1] est %d, La valeur de pipe_fd[0] est %d, La valeur de pipe_fd[1] est %d la valeur de prev_fd est %d\n\n", fds[0], fds[1], pipe_fd[0], pipe_fd[1], prev_fd);
//             // Fork pour exécuter la commande
//             pid = fork();
//             if (pid == -1)
//             {
//                 perror("Erreur de fork");
//                 return (1);
//             }
//             if (pid == 0)
//                 execute_child(fds, pipe_fd, prev_fd, args, env_list, envp);
//             else
//             { // Processus parent
//                 // Fermer les extrémités inutiles
//                 int status;
//                 wait(&status);
//                 if (fds[0] != -1)
//                     close(fds[0]);
//                 if (fds[1] != -1)
//                     close(fds[1]);
//                 if (prev_fd != -1)
//                     close(prev_fd);
//                 if (pipe_fd[1] != -1)
//                     close(pipe_fd[1]);

//                 // Met à jour prev_fd pour la prochaine commande
//                 if (fds[1] != -1)
//                     prev_fd = fds[1];
//                 else
//                     prev_fd = pipe_fd[0];
//             }
//         }
		
//         current = current->next;
//     }
//     while (wait(NULL) > 0);
//     if (args)
//     {
//         if (fds[0] != -1)
//             dup2(fds[0], STDIN_FILENO);
//         else if (fds[0] == -1 && prev_fd != -1)
//             dup2(prev_fd, STDIN_FILENO);
//         exec(args, env_list, envp, 1);
//     }
//     dup2(stdin_save, STDIN_FILENO);
//     dup2(stdout_save, STDOUT_FILENO);
//     close(stdin_save);
//     close(stdout_save);
//     cleanup(fds, prev_fd, pipe_fd, args);
//     return (0);
// }