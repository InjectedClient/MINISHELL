/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/16 14:31:12 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Parcourt et affiche le contenu de la liste lexer.
 */
void	print_lexer_content(t_data *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	while (current != NULL)
	{
		current = current->next;
	}
}

void	looping(char *tmp, t_data *data, t_env *env_list, char **envp)
{
	t_lexer	*tmp_lex;
	char	*processed_cmd;
	int	num_commands;

	if (!tmp)
		exit_all(data);
	if (tmp && tmp[0])
	{
		processed_cmd = add_space(tmp);
		data->input_cmd = processed_cmd;
		lexer_launch(data);
		if (!is_a_directory(data) || !ft_check_parser(data))
			return ;
		tmp_lex = data->lexer_list;
		expand_command(data, env_list);
		num_commands = count_commands(data->lexer_list);
		if (tmp_lex && tmp_lex->cmd_segment)
			execute_token(data->lexer_list, env_list, envp, num_commands);
	}
}

/**
 * Lance le lexer, compte les mots dans la commande d'entrée,
 * traite la chaîne d'entrée et affiche le contenu du lexer.
 */
void	lexer_launch(t_data *data)
{
	int		i;
	t_lexer	*current;
	t_lexer	*tmp;

	tmp = NULL;
	current = NULL;
	data->lexer_list = NULL;
	data->w_count = count_words_in_input(data->input_cmd);
	i = 0;
	process_input_string(data, tmp, current, i);
	print_lexer_content(data);
}
