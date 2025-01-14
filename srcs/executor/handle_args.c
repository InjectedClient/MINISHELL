/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:36 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 13:55:46 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_args(t_lexer *arg)
{
	int	count;

	count = 0;
	while (arg && arg->token == ARG)
	{
		count++;
		arg = arg->next;
	}
	return (count);
}

char	**split_args(t_lexer *cmd)
{
	char	**args;
	int		num_args;
	int		i;

	num_args = 0;
	if (cmd->next && cmd->next->token == ARG)
			num_args = count_args(cmd->next);
	args = malloc(sizeof(char *) * (num_args + 2));
	if (!args)
	{
		perror("malloc");
		return (NULL);
	}
	if (cmd->token == CMD)
		args[0] = ft_strdup(cmd->cmd_segment);
	if (!args[0])
	{
		perror("malloc");
		free_tab(args);
		return (NULL);
	}
	i = 1;
	if (!num_args)
		args[i] = NULL;
	else
	{
		cmd = cmd->next;
		while (cmd && cmd->token == ARG)
		{
			args[i] = ft_strdup(cmd->cmd_segment);
			if (!args[i])
			{
				free_tab(args);
				return (NULL);
			}
			cmd = cmd->next;
			i++;
		}
		args[i] = NULL;
	}
	return (args);
}
