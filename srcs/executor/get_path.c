#include "../../include/minishell.h"

char    *get_cmd_path(char *cmd, char *path_var)
{
    int i;
    char    *exec;
    char    *path_part;
    char    **path;

    path = ft_split(path_var, ':'); // Les paths sont separe par des : ex: PATH=/truc/truc:home/bin/:/blabla on les separ
    if (!path)
        return (NULL);
    i = -1;
    while (path[++i])
    {
        if (!(path_part = ft_strjoin(path[i], "/"))) // On ajoute un / derriere le path part ex : /truc/truc --> /truc/truc/
            free_tab(path);
        exec = ft_strjoin(path_part, cmd); // On ajoute la commande derriere ex: /truc/truc/ --> /truc/truc/cat
        free(path_part);
        if (!exec)
            free_tab(path);
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
