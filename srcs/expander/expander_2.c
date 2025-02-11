/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:53:01 by jle-neze          #+#    #+#             */
/*   Updated: 2025/02/11 12:18:21 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	starts_with_tilde(const char *cmd_segment)
{
	if (!cmd_segment)
		return (0);
	return (cmd_segment[0] == '~');
}

char	*ft_strtrim(const char *str)
{
	char	*end;

	while (*str && isspace((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (ft_strdup(""));
	end = (char *)str + ft_strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;
	return (ft_strndup(str, end - str + 1));
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

char	*expand_variable_name(const char *start, t_env *env_list, size_t len)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(start, 0, len);
	value = ft_getenv(var_name, env_list);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
