/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:58:39 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/15 13:54:59 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv_dup(char *path, t_env *env_list)
{
	if (!path)
	{
		return (NULL);
	}
	while (env_list)
	{
		if (ft_strcmp(env_list->name, path) == 0)
			return (ft_strdup(env_list->value));
		env_list = env_list->next;
	}
	return (NULL);
}

char	*ft_getenv(char *path, t_env *env_list)
{
	if (!path)
		return (NULL);
	while (env_list)
	{
		if (ft_strcmp(env_list->name, path) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	init_path(char **path_var, char ***path, t_env *env_list)
{
	*path_var = NULL;
	*path = NULL;
	*path_var = ft_getenv("PATH", env_list);
	if (!*path_var)
		return (0);
	*path = ft_split(*path_var, ':');
	if (!*path)
		return (0);
	return (1);
}

char	*init_exec(char **path, char **path_part, char *cmd, int i)
{
	char	*exec;

	*path_part = NULL;
	exec = NULL;
	*path_part = ft_strjoin(path[i], "/");
	if (!*path_part)
		return (NULL);
	exec = ft_strjoin(*path_part, cmd);
	if (!exec)
		return (NULL);
	return (exec);
}

char	*get_cmd_path(char *cmd, t_env *env_list)
{
	int		i;
	char	*path_var;
	char	**path;
	char	*path_part;
	char	*exec;

	if (!cmd)
		return (NULL);
	if (init_path(&path_var, &path, env_list) == 0)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		exec = init_exec(path, &path_part, cmd, i);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_tab(path);
			return (exec);
		}
		free(exec);
	}
	free_tab(path);
	return (NULL);
}
