// #include "../../../include/minishell.h"

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