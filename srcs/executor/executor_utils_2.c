#include "../include/minishell.h"

int	exit_with_error(t_lexer **commands, int num_commands)
{
	free_commands(commands, num_commands);
	return (1);
}

void	child_process_1(t_lexer **commands, int i, int num_commands, int pipes[][2], int files[2])
{
	if (handle_redirections(commands[i], &files[0], &files[1]))
		exit(exit_with_error(commands, num_commands));
	if (i > 0 && files[0] == -1)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_commands - 1 && files[1] == -1)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_pipes(num_commands, pipes);
}

void	child_process_2(t_env *env_list, char **envp, int files[2], int i, t_lexer **commands)
{
	char	**args;

	args = split_args(commands[i]);
	if (is_builtin(args[0]))
	{
		g_global = exec_builtins_with_redirections(args, env_list,
				files[0], files[1]);
		exit(g_global);
	}
	exec(args, env_list, envp);
	free_tab(args);
	exit(127);
}

void	end_execute_token(t_lexer **commands, int num_commands, int pipes[][2])
{
	close_pipes(num_commands, pipes);
	wait_for_children(num_commands);
	free_commands(commands, num_commands);
}

int	start_execute_token(t_lexer *lexer_list,
		int num_commands, int pipes[][2], t_lexer ***commands)
{
	if (create_pipes(num_commands, pipes) == 1)
		return (1);
	*commands = split_by_pipe(lexer_list);
	if (!commands)
		return (1);
	return (0);
}
