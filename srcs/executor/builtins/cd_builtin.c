#include "../../../include/minishell.h"

int builtin_cd(char **args)
{
    char *path = args[1]; // Le chemin est le premier argument après "cd"

    if (!path) {
        path = getenv("HOME"); // Si aucun chemin n'est donné, on utilise HOME
        if (!path) {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
    }

    if (chdir(path) != 0) {
        perror("cd");
        return 1; // Erreur
    }
    return 0; // Succès
}
