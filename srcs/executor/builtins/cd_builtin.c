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

char	*oldpwd_path(t_env *current)
{
	char	*path;

	while (current)
	{
		if (ft_strcmp(current->name, "OLDPWD") == 0)
			path = ft_strdup(current->value);
		if (!path)
			return (NULL);
		current = current->next;
	}
	return (path);
}

int	builtin_cd(char **args, t_env **env_list)
{
	char	*path;
	char	*pwd;
	char	cwd[1024];

	if (args[2])
		return (cd_errors("arg"));
	if (!args[1])
	{
		if (!(path = getenv("HOME")))
			return (cd_errors("home"));
		path = ft_strdup(path);
		if (!path)
			return (cd_errors("malloc"));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = oldpwd_path(*env_list);
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
		return (error_cd());
	if (!(pwd = ft_strjoin("OLDPWD=", cwd)))
		return (cd_errors("malloc"));
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
	if (!(pwd = ft_strjoin("PWD=", cwd)))
		return (cd_errors("malloc"));
	update_or_add_env(env_list, pwd);
	free(pwd);
	return (0);
}
