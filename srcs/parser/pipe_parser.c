/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:22 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/22 12:07:36 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Parcourt la liste des tokens et vérifie la syntaxe autour des pipes,
	comme >| ou |<, qui sont incorrects.
	cmd_segment = segment de commande
*/
int	check_invalid_pipes(t_data *data)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	tmp = data->lexer_list;
	while (tmp)
	{
		i = 0;
		if ((tmp->cmd_segment[i] == '>' && tmp->cmd_segment[i + 1] == '|')
			|| (tmp->cmd_segment[i] == '<' && tmp->cmd_segment[i + 1] == '|'))
		{
			printf("minishell: parse error near `|'\n");
			i++;
			return (0);
		}
		if ((tmp->cmd_segment[i] == '|' && tmp->cmd_segment[i + 1] == '<')
			|| (tmp->cmd_segment[i] == '|' && tmp->cmd_segment[i + 1] == '>'))
		{
			printf("minishell: no such file or directory\n");
			i++;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/*
	Vérifie les combinaisons de tokens invalides relatives aux pipes.
*/
int	check_invalid_tokens2(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer_list;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
		{
			tmp = tmp->next;
			if (tmp == NULL || tmp->token == PIPE \
			|| tmp->cmd_segment[0] == '\0')
			{
				printf("syntax error near unexpected token\n");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	if (!check_invalid_tokens(data))
	{
		printf("syntax error near unexpected token `>'\n");
		return (0);
	}
	tmp = data->lexer_list;
	return (1);
}

/*
	Vérifie des combinaisons spécifiques de chevrons et de pipes qui sont
	syntaxiquement incorrectes.
*/
int	check_pipe_bracket(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i - 1] == '>' && str[i + 1] == '<')
			{
				printf("minishell: parse syntax near `|'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
