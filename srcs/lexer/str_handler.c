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
void	process_lexer_input(char *str, int i, int *j, t_quote *state)
{
	while (str[i])
	{
		update_quoting_state(str[i], state);
		if (!ft_white_space(str[i]) && (!state->doubl_quot_status && \
		!state->singl_quot_status))
		{
			(*j)++;
			(i)++;
		}
		else if (ft_white_space(str[i]) && (!state->doubl_quot_status && \
		!state->singl_quot_status))
			break ;
		else if (state->doubl_quot_status || state->singl_quot_status)
		{
			(*j)++;
			(i)++;
		}
	}
}

/**
 * Extrait un mot de la chaîne de caractères et l'ajoute à la liste lexer.
 */
int	get_word_in_list(char *str, int i, t_data *data, t_lexer *tmp)
{
	char	*word;
	int		j;
	int		k;
	t_quote	*state;

	word = NULL;
	k = 0;
	j = 0;
	state = malloc(sizeof(t_quote));
	if (!state)
		return (-1);
	reset_quoting_state(state);
	process_lexer_input(str, i, &j, state);
	word = malloc(sizeof(char) * (j + sizeof('\0')));
	if (!word)
		return (0);
	word[j] = '\0';
	while (k < j)
		word[k++] = str[i++];
	add_lexer_to_end(data, word);
	get_data_in_node(&data->lexer_list);
	get_token_in_node(&data->lexer_list, tmp);
	free(state);
	return (j);
}

/**
 * Traite la chaîne de caractères d'entrée et remplit la liste lexer.
 */
void	process_input_string(char *input_cmd, t_lexer *tmp, t_lexer *current)
{
	int	i;
	int	j;
	int	x;
	t_lexer	*tmp;
	t_lexer	*current;
	t_lexer	*lexer_list;

	tmp = NULL;
	current = NULL;
	x = 0;
	i = 0;
	while (input_cmd[i])
	{
		j = 0;
		while (input_cmd[i] == ' ' || (input_cmd[i] >= '\t' && input_cmd[i] <= '\r'))
			i++;
		// if (!input_cmd || input_cmd[i])
		// {
		// 	lexer_list = NULL;
		// 	get_token_in_node(&current, tmp);
		// 	return ;
		// }
		j = get_word_in_list(input_cmd, i, data, tmp);
		if (x == 0)
			current = data->lexer_list;
		i = i + j;
		x++;
	}
	data->lexer_list = current;
}
