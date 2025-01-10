/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:32:25 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/10 13:36:50 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	error_cd(void)
{
	perror("minishell: cd");
	return (1);
}

int	cd_errors(char *type)
{
	if (ft_strcmp("arg", type) == 0)
		write(2, "minishell: cd: too many arguments\n", 34);
	else if (ft_strcmp("home", type) == 0)
		write(2, "minishell: cd: HOME not set\n", 28);
	else if (ft_strcmp("oldpwd", type) == 0)
		write(2, "minishell: cd: OLDPWD not set\n", 30);
	else if (ft_strcmp("malloc", type) == 0)
		write(2, "minishell: cd: memory allocation error\n", 40);
	return (1);
}

int	builtin_cd(char **args, t_env **env_list)
{
	char	*path;
	char	*pwd;
	char	cwd[1024];

	path = NULL;
	if (args[2])
		return (cd_errors("arg"));
	if (!args[1])
	{
		path = ft_getenv_dup("HOME", *env_list);
		if (!path)
			return (cd_errors("home"));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = ft_getenv_dup("OLDPWD", *env_list);
		if (!path)
			return (cd_errors("oldpwd"));
		printf("%s\n", path);
	}
	else
	{
		path = ft_strdup(args[1]);
		if (!path)
			return (cd_errors("malloc"));
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		free(path);
		return (error_cd());
	}
	pwd = ft_strjoin("OLDPWD=", cwd);
	if (!pwd)
	{
		free(path);
		return (cd_errors("malloc"));
	}
	update_or_add_env(env_list, pwd);
	free(pwd);
	if (chdir(path) != 0)
	{
		free(path);
		return (error_cd());
	}
	free(path);
	if (!getcwd(cwd, sizeof(cwd)))
		return (error_cd());
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (cd_errors("malloc"));
	update_or_add_env(env_list, pwd);
	free(pwd);
	return (0);
}
