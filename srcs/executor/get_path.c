#include "../../include/minishell.h"

char *get_cmd_path(char *cmd, char *path_var) {
    char **paths;
    char *cmd_path;
    char *tmp;
    int i;

    if (!cmd || !path_var)
        return (NULL);
    if (strchr(cmd, '/')) { // Chemin absolu ou relatif
        if (access(cmd, X_OK) == 0)
            return (strdup(cmd));
        return (NULL);
    }
    paths = ft_split(path_var, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i]) {
        tmp = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(cmd_path, X_OK) == 0) {
            free_tab(paths);
            return (cmd_path);
        }
        free(cmd_path);
        i++;
    }
    free_tab(paths);
    return (NULL);
}

