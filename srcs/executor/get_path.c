#include "../../include/minishell.h"

char    *ft_getenv_dup(char *path, t_env *env_list)
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

char    *ft_getenv(char *path, t_env *env_list)
{
    if (!path)
    {
        return (NULL);
    }
	while (env_list)
	{
		if (ft_strcmp(env_list->name, path) == 0)
            return (env_list->value);
		env_list = env_list->next;
	}
    return (NULL);
}

char    *get_cmd_path(char *cmd, t_env *env_list)
{
    int i;
    char    *exec;
    char    *path_part;
    char    **path;
    char    *path_var;

    if (!cmd)
        return (NULL);
    path_var = ft_getenv("PATH", env_list);
    if (!path_var)
        return (NULL);
    path = ft_split(path_var, ':'); // Les paths sont separe par des : ex: PATH=/truc/truc:home/bin/:/blabla on les separ
    if (!path)
        return (NULL);
    i = -1;
    while (path[++i])
    {
        path_part = ft_strjoin(path[i], "/");
        if (!path_part) // On ajoute un / derriere le path part ex : /truc/truc --> /truc/truc/
        {
            free_tab(path);
            return (NULL);
        }
        exec = ft_strjoin(path_part, cmd); // On ajoute la commande derriere ex: /truc/truc/ --> /truc/truc/cat
        free(path_part);
        if (!exec)
        {
            free_tab(path);
            return (NULL);
        }
        if (access(exec, F_OK | X_OK) == 0)
        {
            free_tab(path);
            return (exec);
        }
        free(exec);
    }
    free_tab(path);
    return(NULL);
}
