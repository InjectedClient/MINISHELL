/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:25 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/05 14:09:41 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Cherche si il y a une erreur de syntaxe due à des guillemets non fermés.
	Si les deux indicateurs sont identiques, c'est qu'il +y a une erreur.
*/
int	check_quotes(char *str, t_data *data)
{
	int	i;

	i = 0;
	data->is_sing_quot = 0;
	data->is_doub_quot = 1;
	while (str[i])
	{
		if (str[i] == '"' && !data->is_sing_quot && !data->is_doub_quot)
			data->is_doub_quot = 1;
		else if (str[i] == '"' && !data->is_sing_quot && data->is_doub_quot)
			data->is_doub_quot = 0;
		else if (str[i] == '\'' && !data->is_sing_quot && data->is_doub_quot)
			data->is_sing_quot = 1;
		else if (str[i] == '\'' && data->is_sing_quot && data->is_doub_quot)
			data->is_sing_quot = 0;
		i++;
	}
	if (data->is_sing_quot == data->is_doub_quot)
	{
		printf("quote not closed\n");
		return (0);
	}
	return (1);
}

