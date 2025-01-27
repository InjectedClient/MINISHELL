/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:16 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/27 12:38:15 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ajoute des espaces autour des opérateurs dans la commande donnée.
 */
char	*add_space(const char *command)
{
	size_t	new_len;
	size_t	i;
	char	*new_command;
	t_quote	*state;

	state = malloc(sizeof(t_quote));
	if (!state)
		return (0);
	state->doubl_quot_status = 0;
	state->singl_quot_status = 0;
	new_len = calculate_new_length(command);
	new_command = malloc(new_len + 1);
	if (!new_command)
		return (NULL);
	i = 0;
	fill_command_with_spaces(command, new_command, state, i);
	free(state);
	return (new_command);
}

/**
 * Compte le nombre de mots dans une chaîne de caractères en
 * fonction des espaces.
 */
int	count_words_in_input(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_white_space(str[i]) && str[i])
			i++;
		if (str[i])
			count++;
		while (!ft_white_space(str[i]) && str[i])
			i++;
	}
	return (count);
}

/**
 * Traite l'entrée lexer en mettant à jour l'état des 
 * guillemets et en comptant les mots.
 */
void	process_lexer_input(char *str, int *i, int *j, t_quote *state)
{
	while (str[*i])
	{
		update_quoting_state(str[*i], state);
		if (!ft_white_space(str[*i]) && (!state->doubl_quot_status && \
		!state->singl_quot_status))
		{
			(*j)++;
			(*i)++;
		}
		else if (ft_white_space(str[*i]) && (!state->doubl_quot_status && \
		!state->singl_quot_status))
			break ;
		else if (state->doubl_quot_status || state->singl_quot_status)
		{
			(*j)++;
			(*i)++;
		}
	}
}
void init_kj(int *k, int *j)
{
	*k = 0;
	*j = 0;
}

/**
 * Extrait un mot de la chaîne de caractères et l'ajoute à la liste lexer.
 */
int	get_word_in_list(char *str, int i, t_data *data, t_lexer *tmp)
{
	char	*word;
	int		j;
	int		k;
	int		x;
	t_quote	*state = malloc(sizeof(t_quote)); // Déclaration et initialisation combinées

	if (!state)
		return (0);
	word = NULL;
	x = i;
	init_kj(&k, &j); // Passer les paramètres par référence
	reset_quoting_state(state);
	process_lexer_input(str, &i, &j, state);
	word = malloc(sizeof(char) * (j + sizeof('\0')));
	if (!word)
		return (0);
	word[j] = '\0';
	while (k < j)
		word[k++] = str[x++];
	add_lexer_to_end(data, word);
	get_data_in_node(&data->lexer_list);
	get_token_in_node(&data->lexer_list, tmp);
	free(state);
	return (j);
}

/**
 * Traite la chaîne de caractères d'entrée et remplit la liste lexer.
 */
void	process_input_string(t_data *data, t_lexer *tmp, \
		t_lexer *current, int i)
{
	int	j;
	int	x;

	x = 0;
	while (data->input_cmd[i])
	{
		j = 0;
		while (data->input_cmd[i] == ' ' || \
		(data->input_cmd[i] >= '\t' && data->input_cmd[i] <= '\r'))
			i++;
		if (!data->input_cmd || !data->input_cmd[i])
		{
			data->lexer_list = current;
			get_token_in_node(&current, tmp);
			return ;
		}
		j = get_word_in_list(data->input_cmd, i, data, tmp);
		if (x == 0)
			current = data->lexer_list;
		i = i + j;
		x++;
	}
	data->lexer_list = current;
}
