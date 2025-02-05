/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:18:04 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_lexer *lexer_list)
{
	int		count;
	t_lexer	*current;

	count = 1;
	current = lexer_list;
	while (current)
	{
		if (current->token == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	print_lexer_content(t_data *data)
{
	t_lexer	*current;

	current = data->lexer_list;
	while (current != NULL)
	{
		current = current->next;
	}
}

void	init_data(t_data *data)
{
	data->num_commands = count_commands(data->lexer_list);
	data->commands = NULL;
}

void	looping(char *tmp, t_data *data, t_env *env_list)
{
	t_lexer	*tmp_lex;
	char	*processed_cmd;

	if (!tmp)
		exit_all(data);
	if (tmp && tmp[0])
	{
		processed_cmd = add_space(tmp);
		data->input_cmd = ft_strdup(processed_cmd);
		free(processed_cmd);
		lexer_launch(data);
		if (!is_a_directory(data) || !ft_check_parser(data))
			return ;
		tmp_lex = data->lexer_list;
		expand_command(data, env_list);
		init_data(data);
		if (tmp_lex && tmp_lex->cmd_segment)
			g_global = execute_token(data);
	}
}

/**
 * Lance le lexer, compte les mots dan s la commande d'entrée,
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
