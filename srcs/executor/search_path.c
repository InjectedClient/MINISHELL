#include "../../include/minishell.h"

char    *get_path_from_env(char *name, char *envp[])
{
    int i;
    int len;

    len = ft_strlen(name);
    i = -1;
    while (envp[++i])
    {
        if (ft_strncmp(name, envp[i], len) == 0 && envp[i][len] == '=')
        {
            return (envp[i] + len + 1);
        }
    }
    return (NULL);
}

char    *get_cmd_path(char *cmd, char *envp[])
{
    int i;
    char    *exec;
    char    *path_part;
    char    *check_path;
    char    **path;

    if (!(check_path = get_path_from_env("PATH", envp)))
        return (NULL);
    path = malloc_check(ft_split(check_path, ':')); // Les paths sont separe par des : ex: PATH=/truc/truc:home/bin/:/blabla on les separ
    i = -1;
    while (path[++i])
    {
        if (!(path_part = ft_strjoin(path[i], "/"))) // On ajoute un / derriere le path part ex : /truc/truc --> /truc/truc/
            free_tab_and_exit(path);
        exec = ft_strjoin(path_part, cmd); // On ajoute la commande derriere ex: /truc/truc/ --> /truc/truc/cat
        free(path_part);
        if (!exec)
            free_tab_and_exit(path);
        if (access(exec, F_OK | X_OK) == 0)
        {
            free_array(path);
            return (exec);
        }
        free(exec);
    }
    free_array(path);
    return(NULL);
}
