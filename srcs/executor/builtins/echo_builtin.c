#include "../../../include/minishell.h"

#include <unistd.h>
#include <string.h>

// Fonction utilitaire pour vérifier si une chaîne est uniquement composée de "-n"
int is_only_n_option(const char *arg)
{
    if (!arg || arg[0] != '-')
        return (0);
    for (int i = 1; arg[i]; i++)
    {
        if (arg[i] != 'n')
            return (0);
    }
    return (1);
}

int builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    // Vérifie les options `-n` valides
    while (args[i] && is_only_n_option(args[i]))
    {
        newline = 0;
        i++;
    }

    // Affiche les arguments restants
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1]) // Ajouter un espace sauf après le dernier argument
            write(1, " ", 1);
        i++;
    }

    // Ajoute une nouvelle ligne si `-n` n'est pas spécifié
    if (newline)
        write(1, "\n", 1);

    return (0);
}
