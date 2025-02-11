/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:19:11 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/11 12:20:53 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_variable_expansion(t_expand_args *args)
{
	char	*var_expanded;
	size_t	token_len;
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
		token_len = get_variable_token_length(&args->cmd_segment[*(args->i)]);
		*(args->i) += token_len;
		free(var_expanded);
		return (1);
	}
	free(var_expanded);
	return (0);
}
