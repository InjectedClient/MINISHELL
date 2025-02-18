/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:53:23 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/18 14:10:14 by nlambert         ###   ########.fr       */
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

int	process_heredocs(t_lexer *command, int *infile)
{
	t_lexer	*current;
	int		error;
	int		heredoc_found;

	heredoc_found = 0;
	current = command;
	while (current)
	{
		if (current->token == HERE_DOC)
		{
			heredoc_found = 1;
			break ;
		}
		current = current->next;
	}
	if (heredoc_found)
	{
		error = handle_all_heredocs(command, infile);
		if (error)
			return (error);
		dup2(*infile, STDIN_FILENO);
		*infile = STDIN_FILENO;
	}
	return (0);
}
