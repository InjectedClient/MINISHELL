/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:54 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 13:13:28 by nlambert         ###   ########.fr       */
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
	t_quote	quote_status = {0, 0, 0};

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

char	*expand_variable(const char *input, t_env *env_list,
		int in_single_quote)
{
	const char	*start;
	size_t		len;
	char		*ret;
	char		*remaining;
	char		*result;
	char		*var_name;
	char		*value;

	start = input + 1;
	len = 0;
	if (in_single_quote)
		return (ft_strdup(input));
	if (*start == 34 || *start == '\0')
		return (ft_strdup("$"));
	if (*start == '?')
	{
		ret = ft_itoa(g_global);
		remaining = ft_strdup(start + 1);
		result = ft_strjoin(ret, remaining);
		free(ret);
		free(remaining);
		return (result);
	}
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;
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

char	*expand_token(t_lexer *token, t_env *env_list)
{
	t_quote	quote_status = {0, 0, 0};
	char	*expanded;
	char	*var_expanded;
	int		i;
	int		j;
	size_t	len;

	expanded = malloc(1024);
	i = 0;
	j = 0;
	if (!expanded)
		return (NULL);
	while (token->cmd_segment[i])
	{
		if (token->cmd_segment[i] == '\'' && !quote_status.doubl_quot_status)
		{
			quote_status.singl_quot_status = !quote_status.singl_quot_status;
			i++;
		}
		else if (token->cmd_segment[i] == '\"'
			&& !quote_status.singl_quot_status)
		{
			quote_status.doubl_quot_status = !quote_status.doubl_quot_status;
			i++;
		}
		else if (token->cmd_segment[i] == '$')
		{
			var_expanded = expand_variable(&token->cmd_segment[i],
					env_list, quote_status.singl_quot_status);
			if (var_expanded)
			{
				len = ft_strlen(var_expanded);
				ft_memcpy(&expanded[j], var_expanded, len);
				j += len;
				i += ft_strlen_until(&token->cmd_segment[i], " \t\"\'");
				free(var_expanded);
			}
		}
		else
			expanded[j++] = token->cmd_segment[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

void	expand_command(t_data *data, t_env *env_list)
{
	t_lexer	*current;
	char	*expanded;
	char	*cleaned;

	current = data->lexer_list;
	while (current)
	{
		expanded = expand_token(current, env_list);
		if (!expanded)
		{
			perror("minishell: expansion failed");
			exit(1);
		}
		cleaned = remove_quotes(expanded);
		free(expanded);
		free(current->cmd_segment);
		current->cmd_segment = cleaned;
		current = current->next;
	}
}

size_t	ft_strlen_until(const char *str, const char *stop_chars)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str || !stop_chars)
		return (0);
	while (str[i])
	{
		j = 0;
		while (stop_chars[j])
		{
			if (str[i] == stop_chars[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
