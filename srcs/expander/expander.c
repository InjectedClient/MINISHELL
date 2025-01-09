#include "../../include/minishell.h"

// char *expand_token(const char *token, char **envp)
// {
//     if (is_single_quote(token))
//         return handle_single_quote(token);
//     if (is_double_quote(token))
//         return handle_double_quote(token, envp);
//     if (starts_with_tilde(token))
//         return expand_tilde(token);
//     if (starts_with_dollar(token))
//         return expand_variable(token, envp);

//     return strdup(token); // Si rien à faire, retourne le token tel quel.
// }

// char **expand_command(char **tokens, char **envp) {
//     int i = 0;
//     char **expanded = malloc(sizeof(char *) * (count_tokens(tokens) + 1));

//     while (tokens[i]) {
//         expanded[i] = expand_token(tokens[i], envp);
//         i++;
//     }
//     expanded[i] = NULL; // Terminateur.
//     return expanded;
// }

// char *expand_tilde(const char *input) {
//     if (input[0] != '~') return strdup(input); // Pas une tilde, retourne tel quel.

//     const char *home = getenv("HOME"); // Récupère la valeur de HOME.
//     if (!home) return strdup(input); // Si pas de HOME, retourne tel quel.

//     // Concatène le HOME avec le reste du chemin.
//     return ft_strjoin(home, input + 1); // Exemple d'implémentation avec une fonction custom.
// }

// char *expand_variable(const char *input, char **envp) {
//     if (input[0] != '$') return strdup(input); // Pas une variable, retourner le texte tel quel.

//     char *var_name = extract_var_name(input + 1); // Fonction qui extrait le nom de la variable.
//     char *value = getenv(var_name); // Récupère la valeur.
//     free(var_name);

//     return value ? strdup(value) : strdup(""); // Si la variable n'existe pas, retourne une chaîne vide.
// }
