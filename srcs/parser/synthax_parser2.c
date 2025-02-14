/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_parser2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:07:47 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/14 17:16:10 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Détermine si le segment de commande est un répertoire.
*/
int	check_directory(char *str) //TODO 
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
