#include "../include/minishell.h"

int	handle_append_out(t_lexer *current, int *outfile)
{
	*outfile = open(current->next->cmd_segment,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*outfile == -1)
	{
		perror(current->next->cmd_segment);
		return (1);
	}
	dup2(*outfile, STDOUT_FILENO);
	close(*outfile);
	return (0);
}

int	handle_redirect_out(t_lexer *current, int *outfile)
{
	*outfile = open(current->next->cmd_segment,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
	{
		perror(current->next->cmd_segment);
		return (1);
	}
	dup2(*outfile, STDOUT_FILENO);
	close(*outfile);
	return (0);
}

int	handle_redirect_in(t_lexer *current, int *infile)
{
	*infile = open(current->next->cmd_segment, O_RDONLY);
	if (*infile == -1)
	{
		perror(current->next->cmd_segment);
		return (1);
	}
	dup2(*infile, STDIN_FILENO);
	close(*infile);
	return (0);
}

int	handle_redirections(t_lexer *command, int *infile, int *outfile)
{
	t_lexer	*current;
	int		error;

	*infile = -1;
	*outfile = -1;
	error = 0;
	current = command;
	while (current)
	{
		if (current->token == REDIRECT_IN)
			error = handle_redirect_in(current, infile);
		else if (current->token == REDIRECT_OUT)
			error = handle_redirect_out(current, outfile);
		else if (current->token == APPEND_OUT)
			error = handle_append_out(current, outfile);
		if (error)
			break ;
		current = current->next;
	}
	return (error);
}

int	exec_builtins_with_redirections(char **args, t_env *env_list,
		int infile, int outfile)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (infile != -1)
		dup2(infile, STDIN_FILENO);
	if (outfile != -1)
		dup2(outfile, STDOUT_FILENO);
	status = exec_builtins(args, env_list);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}
