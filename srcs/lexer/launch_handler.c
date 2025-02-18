/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/18 14:11:39 by nlambert         ###   ########.fr       */
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

void	free_lexer_list(t_lexer *list)
{
	t_lexer	*temp;

	while (list)
	{
		temp = list->next;
		if (list->cmd_segment)
			free(list->cmd_segment);
		free(list);
		list = temp;
	}
}

void	free_commands(t_data *data)
{
	int	i;

	i = 0;
	if (data->commands)
	{
		while (data->commands[i])
		{
			free_lexer_list(data->commands[i]);
			i++;
		}
		free(data->commands);
	}
}

void	free_data(t_data *data)
{
	if (data->input_cmd)
	{
		free(data->input_cmd);
		data->input_cmd = NULL;
	}
	if (data->commands)
	{
		free_commands(data);
		data->commands = NULL;
		data->lexer_list = NULL;
	}
	else if (data->lexer_list)
	{
		free_lexer_list(data->lexer_list);
		data->lexer_list = NULL;
	}
}

void	looping(char *tmp, t_data *data, t_env *env_list)
{
	t_lexer	*temp;

	temp = NULL;
	if (!tmp)
		exit_all(data, tmp);
	if (tmp && tmp[0])
	{
		data->input_cmd = add_space(tmp);
		if (!data->input_cmd)
			return ;
		if (process_input_string(data) == 0)
			return ;
		get_data_in_node(&data->lexer_list);
		get_token_in_node(&data->lexer_list, temp);
		if (!is_a_directory(data) || !ft_check_parser(data))
			return ;
		expand_command(data, env_list);
		data->num_commands = count_commands(data->lexer_list);
		if (init_commands(data) == 0)
			return ;
		if (data->lexer_list && data->lexer_list->cmd_segment)
			g_global = execute_token(data, env_list);
	}
}
