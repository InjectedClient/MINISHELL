/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:52:33 by jle-neze          #+#    #+#             */
/*   Updated: 2025/02/04 14:04:11 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variable(const char *input, t_env *env_list,
		int in_single_quote)
{
	const char	*start;
	size_t		len;

	start = input + 1;
	len = 0;
	if (in_single_quote)
		return (ft_strdup(input));
	if (*start == 34 || *start == '\0' || *start == '?')
		return (handle_special_variable(start));
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

int	handle_variable_expansion(t_expand_args *args)
{
	char	*var_expanded;
	size_t	len;

	var_expanded = NULL;
	if (args->cmd_segment[*(args->i)] == '$'
		&& !args->quote_status->singl_quot_status)
		var_expanded = expand_variable(&args->cmd_segment[*(args->i)],
				args->env_list, args->quote_status->singl_quot_status);
	if (args->cmd_segment[*(args->i)] == '~')
		var_expanded = expand_tilde(&args->cmd_segment[*(args->i)],
				args->env_list);
	if (var_expanded)
	{
		len = ft_strlen(var_expanded);
		ft_memcpy(&args->expanded[*(args->j)], var_expanded, len);
		*(args->j) += len;
		*(args->i) += ft_strlen_until(&args->cmd_segment[*(args->i)],
				" \t\"\'");
		free(var_expanded);
		return (1);
	}
	free(var_expanded);
	return (0);
}
