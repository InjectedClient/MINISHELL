/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthaxe_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:27 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 15:35:07 by nlambert         ###   ########.fr       */
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
			printf("syntax error near unexpected token\n");
			return (0);
		}
	}
	return (1);
}

/*
 	Utilise nb_brack et invalid_pipes_check pour check les chevrons + pipes,
	et affiche les messages d'erreurs relatifs aux chevrons et aux pipes.
*/
int	check_token_error(t_data *data)
{
	int i;
	t_lexer *tmp;

	i = 0;
	tmp = NULL;
	tmp = data->lexer_list;
	while (tmp)
	{
		i = 0;
		if (!check_nb_redir(tmp->cmd_segment) || !check_nb_redir (tmp->cmd_segment))
		{
			printf("syntax error 1\n");
			return (0);
		}
		if (tmp->cmd_segment[i] == '|' && tmp->cmd_segment[i + 1] == '|')
		{
			printf("syntax error 2\n");
			return (0);
		}
		if (!check_invalid_pipes(data))
			return (0);
		tmp = tmp->next;
	}
	tmp = data->lexer_list;
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

/*
	Détermine si le segment de commande est un répertoire.
*/
int	check_directory(char *str)
{
	if (!check_slash(str, '/'))
	{
		printf ("minishell: %s: Is a directory\n", str);
		return (0);
	}
	return (1);
}

int	is_a_directory(t_data *data)
{
	if (!check_directory(data->input_cmd))
	{
		return (0);
	}
	return (1);
}
