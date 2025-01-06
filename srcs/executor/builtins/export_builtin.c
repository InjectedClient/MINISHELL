#include "../../../include/minishell.h"

void	print_sorted_env(t_env *env_list)
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


void	add_env_variable(t_env **env_list, char *name, char *value, int equal)
{
	t_env *new_node;
	t_env *current;

	current = *env_list;
	if (!(new_node = malloc(sizeof(t_env))))
	{
		free_2(name, value);
		return ;
	}
	new_node->name = ft_strdup(name);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->equal_sign = equal;
	if (!new_node->name || (value && !new_node->value))
	{
		free_2(name, value);
		free_env_node(new_node);
		return ;
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
	int		equal;
	char	*equal_sign;
	char 	*name;
	char 	*value;
	t_env *current;

	equal = 0;
	current = *env_list;
	value = NULL;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		equal = 1;
		name = ft_substr(arg, 0, equal_sign - arg);
		if (*(equal_sign + 1) != '\0')
			value = ft_strdup(equal_sign + 1);
	}
	else
		name = ft_strdup(arg);
	if (!name || (*(equal_sign + 1) && !value))
	{
		free_2(name, value);
		return ;
	}
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			free_2(name, value);
			return;
		}
		current = current->next;
	}
	add_env_variable(env_list, name, value, equal);
}


int is_valid_env_format(char *arg)
{
	int		i;

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

int	builtin_export(char **args, t_env **env_list)
{
	int		i;

	if (!env_list || !*env_list)
		return (1);
	if (!args[1])
	{
		//print_sorted_env(*env_list);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (is_valid_env_format(args[i]))
			update_or_add_env(env_list, args[i]);
		else
		{
			write(2, "minishell: ", 11);
			write(2, "export: `", 9);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "`: not a valid identifier\n", 26);
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
