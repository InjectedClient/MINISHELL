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

int	init_args_with_args(t_lexer *cmd, char **args, int num_args)
{
	int	i;

	if (num_args == 0)
	{
		args[1] = NULL;
		return (1);
	}
	i = 1;
	while (cmd && cmd->token == ARG)
	{
		args[i] = ft_strdup(cmd->cmd_segment);
		if (!args[i])
		{
			free_tab(args);
			return (0);
		}
		cmd = cmd->next;
		i++;
	}
	args[i] = NULL;
	return (1);
}

char	**split_args(t_lexer *cmd)
{
	char	**args;
	int		num_args;

	while (cmd && cmd->token != CMD)
		cmd = cmd->next;
	if (!cmd)
		return (NULL);
	num_args = 0;
	if (cmd->next && cmd->next->token == ARG)
		num_args = count_args(cmd->next);
	args = malloc(sizeof(char *) * (num_args + 2));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd->cmd_segment);
	if (!args[0])
	{
		free_tab(args);
		return (NULL);
	}
	if (!init_args_with_args(cmd->next, args, num_args))
		return (NULL);
	return (args);
}
