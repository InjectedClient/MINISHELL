/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/14 17:19:13 by nlambert         ###   ########.fr       */
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
		printf()
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
		return ;
	}
	if (tmp && tmp[0])
	{
		data->input_cmd = add_space(tmp);
		if (!data->input_cmd)
		{
			free(data->input_cmd);
			return ;
		}
		data->lexer_list = lexer_launch(data, input_cmd);
		if (!data->lexer_list)
			//TODO eorro
		
		get_data_in_node(&data->lexer_list);
		get_token_in_node(&data->lexer_list, tmp);
		// print_lexer_content(data);
		if (!is_a_directory(data) || !ft_check_parser(data)) //TODO check 2 fois directory
		{
			//TODO Free all 
			return ;
		}
		tmp_lex = data->lexer_list;
		expand_command(data, env_list);
		init_data(data);
		if (tmp_lex && tmp_lex->cmd_segment)
			g_global = execute_token(data->commands, int num->num,commands, t_env *envlist);
	}
	free(data->input_cmd);
	free_lexer_list(&data->lexer_list);
	free_commands(&data->commands);
}

/**
 * Lance le lexer, compte les mots dan s la commande d'entrée,
 * traite la chaîne d'entrée et affiche le contenu du lexer.
 */
void	lexer_launch(char *input_cmd)
{
	//int		i;data
	t_lexer	*current;
	t_lexer	*tmp;

	tmp = NULL;
	current = NULL;
	//data->lexer_list = NULL;
	//data->w_count = count_words_in_input(data->input_cmd);
	//process_input_string(data, tmp, current, i);
	process_input_string(data, input_cmd, tmp, current);
}
