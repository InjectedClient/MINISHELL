/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:53:23 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/13 11:40:42 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_append_out(t_lexer *current, int *outfile)
{
	*outfile = open(current->next->cmd_segment,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*outfile == -1)
	{
		write(2, "minishell: ", 11);
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
		write(2, "minishell: ", 11);
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
		write(2, "minishell: ", 11);
		perror(current->next->cmd_segment);
		return (1);
	}
	dup2(*infile, STDIN_FILENO);
	close(*infile);
	return (0);
}

void	close_fd(int *infile, int *outfile)
{
	if (*infile != -1)
	{
		close(*infile);
		*infile = -1;
	}
	if (*outfile != -1)
	{
		close(*outfile);
		*outfile = -1;
	}
}

int	handle_redirections(t_lexer *command, int *infile, int *outfile)
{
	t_lexer	*current;
	int		error;

	*infile = -1;
	*outfile = -1;
	error = 0;
	current = command;
	error = process_heredoc(command, infile, &current);
	if (error)
		return (error);
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
	if (error)
		close_fd(infile, outfile);
	return (error);
}
