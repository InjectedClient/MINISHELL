// #include "expander.h"
// #include "utils.h"

// char    *expander(char *str)
// {
//     char    *value;
//     char    *exit_status

//     if (!str)
//         return (ft_strdup(""));
//     if (strcmp(str, "$?") == 0)
//     {
//         // Retourne le code de sortie de la dernière commande
//         exit_status = ft_itoa(global_status);
//         return (exit_status);
//     }
//     value = getenv(str);
//     if (value)
//         return (ft_strdup(value));
//     return (ft_strdup(""));
// }