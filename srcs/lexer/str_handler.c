/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:16 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/11 14:39:29 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/**
 * Extrait un mot de la chaîne de caractères et l'ajoute à la liste lexer.
 */

void	init_kj(int *k, int *j)
{
	*k = 0;
	*j = 0;
}

int free_word_and_state(char **word, t_quote **state)
{
	if (*word)
	{
		free(*word);
		*word = NULL;
	}
	if (*state)
	{
		free(*state);
		*state = NULL;
	}
	return (-1);
}

int	get_word_in_list(char *str, int i, t_data *data)
{
	t_quote	*state;
	char	*word;
	int		j;
	int		k;
	int		x;

	state = NULL;
	word = NULL;
	init_kj(&k, &j);
	x = i;
	state = malloc(sizeof(t_quote));
	if (!state)
		return (-1);
	reset_quoting_state(state);
	process_lexer_input(str, &i, &j, state);
	word = malloc(sizeof(char) * (j + sizeof('\0')));
	if (!word)
		return (free_word_and_state(&word, &state));
	word[j] = '\0';
	while (k < j)
		word[k++] = str[x++];
	if (add_lexer_to_end(data, word) == 0)
		return (free_word_and_state(&word, &state));
	free(state);
	return (j);
}

/**
 * Traite la chaîne de caractères d'entrée et remplit la liste lexer.
 */
int	process_input_string(t_data *data)
{
	t_lexer	*tmp;
	t_lexer	*current;
	int	j;
	int	x;
	int	i;

	tmp = NULL;
	current = NULL;
	x = 0;
	i = 0;
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
			return (1);
		}
		j = get_word_in_list(data->input_cmd, i, data);
		if (j == -1)
			return (0);
		if (x == 0)
			current = data->lexer_list;
		i = i + j;
		x++;
	}
	data->lexer_list = current;
	return (1);
}
