/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:54 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/04 16:05:36 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quote	init_quote_status(void)
{
	t_quote	quote_status;

	quote_status.singl_quot_status = 0;
	quote_status.doubl_quot_status = 0;
	quote_status.singl_quot_start_status = 0;
	return (quote_status);
}

void	init_i_j(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*expand_token(t_lexer *token, t_env *env_list)
{
	t_quote			quote_status;
	char			*expanded;
	int				i;
	int				j;
	t_expand_args	args;

	init_i_j(&i, &j);
	quote_status = init_quote_status();
	expanded = malloc(sizeof(char) * 4200);
	if (!expanded)
		return (NULL);
	args = (t_expand_args){token->cmd_segment,
		env_list, &quote_status, expanded, &i, &j};
	while (token->cmd_segment[i])
	{
		if (handle_single_quote(&args))
			continue ;
		if (handle_double_quote(&args))
			continue ;
		if (handle_variable_expansion(&args))
			continue ;
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
			continue ;
		}
		cleaned = remove_quotes(expanded);
		free(expanded);
		if (!cleaned)
		{
			perror("minishell: expansion failed");
			continue ;
		}
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
