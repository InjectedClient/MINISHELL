#include "../../../include/minishell.h"

int builtin_cd(char **args)
{
    char *path;

    path = args[1]; // Le chemin est le premier argument après "cd"
    if (!path) {
        path = getenv("HOME"); // Si aucun chemin n'est donné, on utilise HOME
        if (!path) {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (1);
        }
    }
    if (args[2])
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    if (access(path, F_OK) != 0)
    {
        perror("minishell: cd");
        return (1);
    }
    if (chdir(path) != 0) {
        perror("minishell: cd");
        return (1); // Erreur
    }
    return (0); // Succès
}
