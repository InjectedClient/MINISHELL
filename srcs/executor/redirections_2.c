/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:37 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/18 14:10:56 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirections(t_lexer *command, int *infile, int *outfile)
{
	t_lexer	*current;
	int		error;

	*infile = -1;
	*outfile = -1;
	error = process_heredocs(command, infile);
	if (error)
		return (error);
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
	if (error)
		close_fd(infile, outfile);
	return (error);
}
