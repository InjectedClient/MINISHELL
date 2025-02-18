/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:28:59 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/18 13:29:34 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Traite la chaîne de caractères d'entrée et remplit la liste lexer.
 */
static	int	process_token(t_data *data, int *i, int *x, t_lexer **current)
{
	int	j;

	while (data->input_cmd[*i] == ' ' || \
		(data->input_cmd[*i] >= '\t' && data->input_cmd[*i] <= '\r'))
		(*i)++;
	if (!data->input_cmd || !data->input_cmd[*i])
	{
		data->lexer_list = *current;
		get_token_in_node(current, NULL);
		return (2);
	}
	j = get_word_in_list(data->input_cmd, *i, data);
	if (j == -1)
		return (-1);
	if (*x == 0)
		*current = data->lexer_list;
	*i += j;
	(*x)++;
	return (1);
}

int	process_input_string(t_data *data)
{
	int		i;
	int		x;
	int		ret;
	t_lexer	*current;

	i = 0;
	x = 0;
	current = NULL;
	while (data->input_cmd[i])
	{
		ret = process_token(data, &i, &x, &current);
		if (ret == -1)
			return (0);
		if (ret == 2)
			return (1);
	}
	data->lexer_list = current;
	return (1);
}
