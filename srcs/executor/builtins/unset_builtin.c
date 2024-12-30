#include "../../../include/minishell.h"

void remove_env_variable(t_env *env_list, char *var)
{
    t_env *current = env_list, *prev = NULL;

    while (current)
    {
        if (ft_strncmp(current->name, var, ft_strlen(current->name)) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                env_list = current->next;
            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int builtin_unset(char **args, t_env *env_list)
{
    int i = 1;

    while (args[i])
    {
        remove_env_variable(env_list, args[i]);
        i++;
    }
    return (0);
}

// int builtin_unset(char **args)
// {

// }

// //////////////////////////////////GOAL/////////////////////////////
// int env_length(char **env) {
//     int len = 0;
//     while (env[len] != NULL)
//         len++;
//     return len;
// }

// // Fonction `unset` : supprime une variable d'environnement
// void builtin_unset(char *key, char ***env) {
//     if (!key || !*env) {
//         fprintf(stderr, "unset: argument invalide\n");
//         return;
//     }

//     int len = env_length(*env);
//     for (int i = 0; i < len; i++) {
//         // Vérifie si la clé correspond
//         if (strncmp((*env)[i], key, strlen(key)) == 0 && (*env)[i][strlen(key)] == '=') {
//             free((*env)[i]); // Libère la variable supprimée

//             // Décale les éléments suivants
//             for (int j = i; j < len - 1; j++) {
//                 (*env)[j] = (*env)[j + 1];
//             }

//             (*env)[len - 1] = NULL; // Terminer par NULL
//             return;
//         }
//     }

//     fprintf(stderr, "unset: '%s' introuvable\n", key); // Si la variable n'est pas trouvée
// }