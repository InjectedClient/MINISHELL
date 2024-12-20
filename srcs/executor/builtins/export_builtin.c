// #include "../../../include/minishell.h"

// int builtin_export(char **args, char ***envp)
// {
//     char    *key;
//     char    *value;
//     int eq_pos;
//     int i;
//     int j;
//     int key_len;

//     i = 1;
//     while (args[i])
//     {
//         eq_pos = find_char(args[i]);
//         if (eq_pos == -1)
//         {

//         }
//         key = ft_strndup(args[i], eq_pos);
//         value = ft_strdup(args[i] + eq_pos + 1);
//         if (!key)
//         {
//             perror("export");
//             free(key);
//             free(value);
//             return (error());
//         }
//         key_len = ft_strlen(key);
//         j = 0;
//         while ((*envp)[j])
//         {
//             if (ft_strncmp((*envp)[j], key, key_len) == 0 && (*envp)[j][key_len] == '=')
//             {
//                 free((*envp)[j]); // Supprime l'ancienne entrée
//                 (*envp)[j] = ft_strdup(args[i]); // Ajoute la nouvelle
//                 free(key);
//                 free(value);
//                 return (0);
//             }
//         }


//     }
// }
// //////////////////////////////////////////////////////////////////GGOAL///////////////
// // Fonction pour compter les variables d'environnement
// int env_length(char **env) {
//     int len = 0;
//     while (env[len] != NULL)
//         len++;
//     return len;
// }

// // Fonction pour vérifier si une chaîne contient un caractère spécifique
// int contains_char(const char *str, char c) {
//     while (*str) {
//         if (*str == c)
//             return 1;
//         str++;
//     }
//     return 0;
// }

// // Fonction export : ajoute ou met à jour une variable d'environnement
// void builtin_export(char *env_var, char ***env) {
//     if (!env_var || !contains_char(env_var, '=')) {
//         fprintf(stderr, "export: mauvais format, clé=valeur attendu\n");
//         return;
//     }

//     char *key = strdup(env_var); // Copie pour manipulation
//     char *value = strchr(key, '='); // Trouver le '='
//     if (value == NULL) {
//         free(key);
//         return;
//     }
//     *value = '\0'; // Séparer la clé et la valeur
//     value++;

//     int len = env_length(*env);

//     // Rechercher si la clé existe déjà
//     for (int i = 0; i < len; i++) {
//         if (strncmp((*env)[i], key, strlen(key)) == 0 && (*env)[i][strlen(key)] == '=') {
//             free((*env)[i]); // Supprime l'ancienne variable
//             (*env)[i] = strdup(env_var); // Ajoute la nouvelle version
//             free(key);
//             return;
//         }
//     }

//     // Ajouter une nouvelle variable
//     char **new_env = realloc(*env, (len + 2) * sizeof(char *));
//     if (!new_env) {
//         perror("realloc");
//         free(key);
//         return;
//     }

//     new_env[len] = strdup(env_var); // Ajouter la nouvelle chaîne
//     new_env[len + 1] = NULL;        // Terminer par NULL
//     *env = new_env;

//     free(key);
// }