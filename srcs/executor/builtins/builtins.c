#include "builtins.h"

int num_builtins() {
    return sizeof(builtins) / sizeof(builtin_t);
}

int execute_builtin(char **args) {
    if (args == NULL || args[0] == NULL) {
        return 0; // Pas de commande, rien à exécuter
    }

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtins[i].name) == 0) {
            // Appelle la fonction correspondante au builtin
            return builtins[i].func(args);
        }
    }

    return -1; // Retourne -1 si ce n'est pas un builtin
}