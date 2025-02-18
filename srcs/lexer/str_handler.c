/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:16 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/18 13:29:13 by nlambert         ###   ########.fr       */
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
