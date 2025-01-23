/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:53:01 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/23 13:53:08 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	starts_with_tilde(const char *cmd_segment)
{
	if (!cmd_segment)
		return (0);
	return (cmd_segment[0] == '~');
}

int	starts_with_dollar(const char *cmd_segment)
{
	if (!cmd_segment)
		return (0);
	return (cmd_segment[0] == '$');
}

char	*remove_quotes(const char *input)
{
	char	*result;
	int		i;
	int		j;
	t_quote	quote_status;

	quote_status = init_quote_status();
	result = malloc(ft_strlen(input) + 1);
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !quote_status.doubl_quot_status)
			quote_status.singl_quot_status = !quote_status.singl_quot_status;
		else if (input[i] == '\"' && !quote_status.singl_quot_status)
			quote_status.doubl_quot_status = !quote_status.doubl_quot_status;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*handle_special_variable(const char *start)
{
	char	*ret;
	char	*remaining;
	char	*result;

	if (*start == '?')
	{
		ret = ft_itoa(g_global);
		remaining = ft_strdup(start + 1);
		result = ft_strjoin(ret, remaining);
		free(ret);
		free(remaining);
		return (result);
	}
	return (ft_strdup("$"));
}

char	*expand_variable_name(const char *start,
		t_env *env_list, size_t len)
{
	char	*var_name;
	char	*value;
	char	*remaining;
	char	*result;

	var_name = ft_substr(start, 0, len);
	value = ft_getenv(var_name, env_list);
	free(var_name);
	if (value)
	{
		remaining = ft_strdup(start + len);
		result = ft_strjoin(value, remaining);
		free(remaining);
		return (result);
	}
	return (ft_strdup(""));
}
