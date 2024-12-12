/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:26 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 15:35:01 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Vérifie qu'il n'y ait pas plus de deux chevrons à la suite.
*/
int	check_nb_redir(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			j++;
		}
		i++;
	}
	if (j > 2)
		return (0);
	return (1);
}

/*
	Vérifie si les caractères après un symbole de redirection forment une
	combinaison valide.
*/
int	check_redirections(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] == '\0')
		return (0);
	if ((str[i] == '>' && str[i + 1] == '>') \
	|| (str[i] == '>' && str[i + 1] == '<') \
	|| (str[i] == '<' && str[i + 1] == '<') \
	|| (str[i] == '<' && str[i + 1] == '>'))
	{
		if (str[i + 2] == '\0')
			return (0);
	}
	return (1);
}

/*
	Utilise une liste chainee pour verif que les tokens de redirection sont suivis par des éléments valides.
*/
int	check_redirection_arg(t_data *data)
{
	t_lexer	*check;

	check = data->lexer_list;
	while (check != NULL)
	{
		if (check->token == REDIRECT_OUT || check->token == APPEND_OUT \
		|| check->token == REDIRECT_OUTIN || check->token == REDIRECT_IN \
		|| check->token == HERE_DOC || check->token == REDIRECT_INOUT)
		{
			check = check->next;
			if (check == NULL || check->cmd_segment[0] == '\0')
			{
				printf("syntax error\n");
				return (0);
			}
		}
		check = check->next;
	}
	check = data->lexer_list;
	return (1);
}

/*
	Vérifie les combinaisons de tokens invalides relatives aux redirections
	et aux heredoc.
*/
int	check_invalid_tokens(t_data *data)
{
	t_lexer *tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if ((tmp->token == APPEND_OUT || tmp->token == REDIRECT_OUT))
		{
			if (tmp->next->token == HERE_DOC || tmp->next->token == REDIRECT_IN
				|| tmp->next->token == APPEND_OUT
				|| tmp->next->token == REDIRECT_OUT
				|| tmp->next->token == PIPE)
				return (0);
		}
		if (tmp->token == HERE_DOC || tmp->token == REDIRECT_IN)
		{
			if (tmp->next->token == HERE_DOC || tmp->next->token == REDIRECT_IN
				|| tmp->next->token == APPEND_OUT
				|| tmp->next->token == REDIRECT_OUT
				|| tmp->next->token == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
