/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthaxe_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:27 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/11 16:09:07 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	vérifie les erreurs avec les pipes (|) et les redirections en début de
	commande. Signale une erreur si un pipe est utilisé seul ou si les
	redirections sont mal formées.
*/
int	check_cmd_start(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|' && str[1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		return (0);
	}
	if (str[0] == '|')
	{
		printf("minishell:  syntax error near unexpected token `|'\n");
		return (0);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		if (!check_redirections(str))
		{
			printf("minishell : syntax error near unexpected token\n");
			return (0);
		}
	}
	return (1);
}

/*
 	Utilise nb_brack et invalid_pipes_check pour check les chevrons + pipes,
	et affiche les messages d'erreurs relatifs aux chevrons et aux pipes.
*/
int	ft_strcmp_che(char *str)
{
	if (str[0] && str[1])
	{
		if (str[0] == '<' && str[1] == '<')
			return (1);
	}
	return (0);
}

int	check_token_error3(t_data *data, t_lexer *tmp, int flag)
{
	int		i;

	while (tmp)
	{
		i = 0;
		if (!flag)
		{
			if (!tmp->cmd_segment || !nb_redir(tmp->cmd_segment))
				return (0);
		}
		if (tmp->cmd_segment[i] == '|' && tmp->cmd_segment[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			return (0);
		}
		if (!check_invalid_pipes(data))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_token_error(t_data *data)
{
	int		flag;
	t_lexer	*tmp;

	flag = 0;
	if (!data || !data->lexer_list)
		return (0);
	tmp = data->lexer_list;
	if (tmp[0].token == 0)
		flag = 1;
	if (check_token_error3(data, tmp, flag) == 0)
		return (0);
	return (1);
}

/*
	vérifie si le premier caractère est un slash ou un tiret suivi par
	certains caractères spécifiques.
*/
int	check_slash(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[0] == c && str[1] == '\0'))
			return (0);
		if ((str[0] == c && str[1] == c))
			return (0);
		if ((str[0] == c && str[1] == '.'))
			return (0);
		i++;
	}
	return (1);
}
