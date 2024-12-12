/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:46:16 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 16:17:50 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Vérifie le nombre de caractères de redirection dans la commande.
 */
int check_redirect(const char *cmd, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			count++;
		else if (count > 0 && cmd[i] != c)
			return (count);
		i++;
	}
	return (count);
}

/**
 * Vérifie les erreurs de redirection dans le segment de commande.
 */
int check_redir_error(t_lexer *tmp)
{
	int count;

	if (!tmp || !tmp->cmd_segment)
		return (-1);
	if (tmp->cmd_segment[0] == '<')
	{
		count = check_redirect(tmp->cmd_segment, '<');
		if (count > 2 || count == 0)
			return (-1);
	}
	else if (tmp->cmd_segment[0] == '>')
	{
		count = check_redirect(tmp->cmd_segment, '>');
		if (count > 2 || count == 0)
			return (-1);
	}
	return (0);
}

/**
 * Détermine le type de redirection en fonction du segment de commande.
 */
t_token which_redir(t_lexer *tmp)
{
	if (!check_redir_error(tmp))
	{
		if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '\0')
			return (REDIRECT_OUT);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '\0')
			return (REDIRECT_IN);
		else if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '>')
			return (APPEND_OUT);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '<')
			return (HERE_DOC);
		else if (tmp->cmd_segment[0] == '<' && tmp->cmd_segment[1] == '>')
			return (REDIRECT_INOUT);
		else if (tmp->cmd_segment[0] == '>' && tmp->cmd_segment[1] == '<')
			return (REDIRECT_OUTIN);
	}
	return (-1);
}
