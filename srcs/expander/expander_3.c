/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:52:33 by jle-neze          #+#    #+#             */
/*   Updated: 2025/02/11 13:33:13 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(const char *input, t_env *env_list,
		int in_single_quote)
{
	const char	*start;
	size_t		len;

	start = input + 1;
	if (*start && (ft_isdigit(*start) || *start == '='))
	{
		if (*start == '=')
			return (ft_strdup(input));
		return (ft_strdup(""));
	}
	if (in_single_quote)
		return (ft_strdup(input));
	if (*start == '"' || *start == '\0' || *start == '?')
		return (handle_special_variable(start));
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
	return (expand_variable_name(start, env_list, len));
}

char	*expand_tilde(const char *input, t_env *env_list)
{
	char	*home;

	if (input[0] != '~')
		return (ft_strdup(input));
	home = ft_getenv("HOME", env_list);
	if (!home)
		return (ft_strdup(input));
	return (ft_strjoin(home, input + 1));
}

int	handle_single_quote(t_expand_args *args)
{
	if (args->cmd_segment[*(args->i)] == '\''
		&& !args->quote_status->doubl_quot_status)
	{
		args->quote_status->singl_quot_status
			= !args->quote_status->singl_quot_status;
		if (args->quote_status->singl_quot_status)
			args->expanded[(*(args->j))++] = args->cmd_segment[(*(args->i))++];
		else
			(*(args->i))++;
		return (1);
	}
	return (0);
}

int	handle_double_quote(t_expand_args *args)
{
	if (args->cmd_segment[*(args->i)] == '"'
		&& !args->quote_status->singl_quot_status)
	{
		args->quote_status->doubl_quot_status
			= !args->quote_status->doubl_quot_status;
		if (args->quote_status->doubl_quot_status)
			args->expanded[(*(args->j))++] = args->cmd_segment[(*(args->i))++];
		else
			(*(args->i))++;
		return (1);
	}
	return (0);
}

size_t	get_variable_token_length(const char *input)
{
	size_t	len;

	len = 1;
	if (!input[len])
		return (len);
	if (input[len] == '"' || input[len] == '?' || input[len] == '=' || \
	ft_isdigit(input[len]))
		return (len + 1);
	while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
		len++;
	return (len);
}
