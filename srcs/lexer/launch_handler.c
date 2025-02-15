/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/13 12:46:08 by nlambert         ###   ########.fr       */
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
	char *input_cmd;

	if (!tmp)
	{
		free(tmp);
		exit_all(data);
		return ;
	}
	if (tmp && tmp[0])
	{
		data->input_cmd = add_space(tmp);
		data->lexer_list = lexer_launch(data, input_cmd);
		if (!data->lexer_list)
		{
			free_lexer_list(&data->lexer_list);
			exit_all(data);
			return ;
		}
		get_data_in_node(&data->lexer_list);
		get_token_in_node(&data->lexer_list, tmp);
		if (!ft_check_parser(data))
		{
			free_data(data);
			return ;
		}
		tmp_lex = data->lexer_list;
		expand_command(data, env_list);
		init_data(data);
		if (tmp_lex && tmp_lex->cmd_segment)
			g_global = execute_token(data);
	}
	free_data(data);
}

/**
 * Lance le lexer, compte les mots dan s la commande d'entrée,
 * traite la chaîne d'entrée et affiche le contenu du lexer.
 */
t_lexer	*lexer_launch(t_data *data, char *input_cmd)
{
	t_lexer	*current;
	t_lexer	*tmp;

	tmp = NULL;
	current = NULL;
	process_input_string(data, input_cmd, tmp, current);
}
