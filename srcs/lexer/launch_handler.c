/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 16:30:40 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 * Lance le lexer et vérifie si le résultat est un répertoire ou si le parser est valide.
 */
void test_cmd(t_data *data)
{
	lexer_launch(data);
	if (!is_a_directory(data) || !ft_check_parser(data))
		return;
}

/**
 * Parcourt et affiche le contenu de la liste lexer.
 */
void print_lexer_content(t_data *data)
{
	t_lexer *current;

	current = data->lexer_list;
	while (current != NULL)
	{
		printf("Token type: %d\n", current->token);
		current = current->next;
	}
}

/**
 * Traite la commande temporaire, ajoute des espaces autour des opérateurs,
 * lance le lexer et vérifie si le résultat est un répertoire ou si le parser est valide.
 */
char **looping(char *tmp, t_data *data)
{
	t_lexer *tmp_lex;
	char *processed_cmd;
	char **cmd_tab;

	if (tmp && tmp[0])
	{
		processed_cmd = add_space(tmp);
		data->input_cmd = processed_cmd;
		lexer_launch(data);
		if (!is_a_directory(data) || !ft_check_parser(data))
			return (NULL);
		tmp_lex = data->lexer_list;
		cmd_tab = convert_list_to_array(tmp_lex);
		return (cmd_tab);
	}
	return (NULL);
}

/**
 * Lance le lexer, compte les mots dans la commande d'entrée,
 * traite la chaîne d'entrée et affiche le contenu du lexer.
 */
void lexer_launch(t_data *data)
{
	int i;
	t_lexer *current;
	t_lexer *tmp;

	tmp = NULL;
	current = NULL;
	data->lexer_list = NULL;
	data->w_count = count_words_in_input(data->input_cmd);
	i = 0;
	process_input_string(data, tmp, current, i);
	print_lexer_content(data);
}
