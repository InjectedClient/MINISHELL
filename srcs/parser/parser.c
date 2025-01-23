/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:08:29 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 16:16:47 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_parser(t_data *data)
{
	int	count;

	count = 1;
	if (!check_quotes(data->input_cmd, data))
		count = 0;
	else if (!check_cmd_start(data->input_cmd))
		count = 0;
	else if (!check_token_error(data))
		count = 0;
	else if (!check_redirection_arg(data))
		count = 0;
	else if (!check_invalid_tokens2(data))
		count = 0;
	else if (!check_directory(data->input_cmd))
		count = 0;
	else if (!check_pipe_bracket(data->input_cmd))
		count = 0;
	if (count == 0)
	{
		g_global = 2;
		return (0);
	}
	return (1);
}
