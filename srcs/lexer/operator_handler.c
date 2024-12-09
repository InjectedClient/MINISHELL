/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:13 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/05 16:00:38 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Vérifie si le caractère est un opérateur.
 */
int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

/**
 * Vérifie si les caractères à la position donnée forment un opérateur specifique.
 */
int is_double_operator(const char *command, size_t pos)
{
	return ((command[pos] == '<' && command[pos + 1] == '<') || \
			(command[pos] == '<' && command[pos + 1] == '>') || \
			(command[pos] == '>' && command[pos + 1] == '<') || \
			(command[pos] == '>' && command[pos + 1] == '>'));
}

/*
 * Calcule la nouvelle longueur de la commande après ajout des espaces autour des opérateurs.
*/
size_t calculate_new_length(const char *command)
{
	size_t new_len;
	size_t i;

	i = 0;
	new_len = 0;
	while (command[i])
	{
		if (is_double_operator(command, i))
		{
			new_len += 4;
			i++;
		}
		else if (is_operator(command[i]))
			new_len += 3;
		else
			new_len++;
		i++;
	}
	return (new_len);
}

/**
 * Remplit la nouvelle commande avec des espaces autour des opérateurs.
 */
void fill_command_with_spaces(const char *command, char *new_command, t_quote *state, size_t i)
{
	size_t j;

	j = 0;
	while (command[i])
	{
		update_quoting_state(command[i], state);
		if (is_double_operator(command, i) && (!state->doubl_quot_status && !state->singl_quot_status))
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i++];
			new_command[j++] = command[i++];
			new_command[j++] = ' ';
		}
		else if (is_operator(command[i]) && (!state->doubl_quot_status && !state->singl_quot_status))
		{
			new_command[j++] = ' ';
			new_command[j++] = command[i++];
			new_command[j++] = ' ';
		}
		else
			new_command[j++] = command[i++];
	}
	new_command[j] = '\0';
}
