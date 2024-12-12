/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:45:59 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 15:34:34 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Vérifie si le token précédent est une redirection.
 */
int check_prev(t_lexer *token)
{
	return (token->prev->token == APPEND_OUT \
		|| token->prev->token == REDIRECT_IN \
		|| token->prev->token == REDIRECT_OUT \
		|| token->prev->token == REDIRECT_INOUT);
}
/**
 * Attribue le token CMD ou ARG en fonction du premier token.
 */
void cmd_or_arg(t_lexer *tmp, t_lexer *first)
{
	if (first->token != CMD)
		tmp->token = CMD;
	else
		tmp->token = ARG;
}
/*
 * Attribue les tokens appropriés aux éléments de la liste lexer_list.

void get_token_in_node(t_lexer **lexer_list, t_lexer *tmp)
{
	t_lexer *first;

	tmp = *lexer_list;
	while (tmp)
	{
		if (tmp->segment_position == 1)
			first = tmp;
		if (tmp->segment_position == 1 && tmp->cmd_segment[0] != '<' \
		&& tmp->cmd_segment[0] != '>')
			tmp->token = CMD;
		else if (tmp->segment_position == 0)
			tmp->token = PIPE;
		else if (tmp->cmd_segment[0] == '<' || tmp->cmd_segment[0] == '>')
			tmp->token = which_redir(tmp);
		else if (check_prev(tmp))
			tmp->token = FD;
		else if (tmp->prev->token == HERE_DOC)
			tmp->token = DELIMITER;
		else if ((tmp->prev->token == FD || tmp->prev->token == DELIMITER)
			&& (!tmp->next || tmp->next->cmd_segment[0] == '|' || tmp->next))
			cmd_or_arg(tmp, first);
		else
			tmp->token = ARG;
		tmp = tmp->next;
	}
}*/

void get_token_in_node(t_lexer **lexer_list, t_lexer *tmp)
{
    t_lexer *first;

    tmp = *lexer_list;
    while (tmp)
    {
        if (tmp->segment_position == 1)
            first = tmp;
        if (tmp->segment_position == 1 && tmp->cmd_segment[0] != '<' \
        && tmp->cmd_segment[0] != '>')
        {
            tmp->token = CMD;
        }
        else if (tmp->segment_position == 0)
        {
            tmp->token = PIPE;
        }
        else if (tmp->cmd_segment[0] == '<' || tmp->cmd_segment[0] == '>')
        {
            tmp->token = which_redir(tmp);
        }
        else if (check_prev(tmp))
        {
            tmp->token = FD;
        }
        else if (tmp->prev->token == HERE_DOC)
        {
            tmp->token = DELIMITER;
        }
        else if ((tmp->prev->token == FD || tmp->prev->token == DELIMITER)
            && (!tmp->next || tmp->next->cmd_segment[0] == '|' || tmp->next))
        {
            cmd_or_arg(tmp, first);
        }
        else
        {
            tmp->token = ARG;
        }
        tmp = tmp->next;
    }
}
