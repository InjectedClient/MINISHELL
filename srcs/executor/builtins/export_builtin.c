#include "../../../include/minishell.h"

void print_sorted_env(t_env *env_list)
{
    t_env *current = env_list;

    while (current)
    {
        write(1, "declare -x ", 11); // Préfixe
        write(1, current->name, ft_strlen(current->name)); // Nom de la variable

        if (current->value) // Si la variable a une valeur
        {
            write(1, "=\"", 2); // Ajout du `="`
            write(1, current->value, ft_strlen(current->value)); // Valeur de la variable
            write(1, "\"", 1); // Fermeture des guillemets
        }
        write(1, "\n", 1); // Nouvelle ligne
        current = current->next;
    }
}


int is_valid_env_format(char *arg)
{
    int i;

    if (!ft_isalpha(arg[0]) && arg[0] != '_')
        return (0);
    i = 1;
    while (arg[i] && arg[i] != '=')
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void add_env_variable(t_env **env_list, char *name, char *value)
{
    t_env *new_node = malloc(sizeof(t_env));
    t_env *current = *env_list;

    new_node->name = ft_strdup(name);
    if (!new_node->name)
    {
        free(new_node);
        return; // Gérer l'erreur de strdup
    }

    new_node->value = ft_strdup(value);
    if (!new_node->value)
    {
        free(new_node->name);
        free(new_node);
        return; // Gérer l'erreur de strdup
    }
    new_node->next = NULL;

    if (!current)
        *env_list = new_node;
    else
    {
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

void update_or_add_env(t_env **env_list, char *arg)
{
    char *equal_sign = ft_strchr(arg, '=');
    char *name = NULL;
    char *value = NULL;

    if (equal_sign)
    {
        name = ft_substr(arg, 0, equal_sign - arg);
        value = ft_strdup(equal_sign + 1);
    }
    else
    {
        name = ft_strdup(arg);
        value = NULL; // Valeur vide si pas de '='
    }

    if (!name)
        return; // Pas besoin de libérer car `value` est NULL ou géré par ft_strdup

    t_env *current = *env_list;
    while (current)
    {
        if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
        {
            free(current->value);
            current->value = value;
            free(name);
            return;
        }
        current = current->next;
    }
    add_env_variable(env_list, name, value); // Passe directement env_list
}




int builtin_export(char **args, t_env *env_list)
{
    int i;

    if (!args[1])
    {
        print_sorted_env(env_list); 
        return (0);
    }
    i = 1;
    while (args[i])
    {
        if (is_valid_env_format(args[i]))
            update_or_add_env(&env_list, args[i]);
        else
        {
            write(2, "export: `", 9); // Message d'erreur standard
            write(2, args[i], ft_strlen(args[i])); // Nom de l'argument
            write(2, "`: not a valid identifier\n", 25); // Suite du message
        }
        i++;
    }
    return (0);
}

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