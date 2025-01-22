/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:23:01 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/14 16:23:36 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "cd";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "exit";
	builtins[4] = "pwd";
	builtins[5] = "export";
	builtins[6] = "unset";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtins(char **args, t_env *env_list)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (builtin_echo(args));
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (builtin_cd(args, &env_list));
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (builtin_export(args, &env_list));
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (builtin_unset(args, &env_list));
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (builtin_env(env_list));
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (builtin_exit(args));
	else
		return (-1);
}
