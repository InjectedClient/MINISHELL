#include "../include/minishell.h"

// int is_builtin(char *cmd)
// {
//     int i;
//     char *builtins[] = {"cd", "env", "echo", "exit", "pwd", "export", "unset", NULL};

//     i = 0;
//     while (builtins[i])
//     {
//         if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
//             return (1);
//         i++;
//     }
//     return (0); // Retourne 0 si ce n'est pas un builtin
// }

// int exec_builtins(char **args, t_env *env_list) 
// {
//     if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
//         return (builtin_echo(args));
//     else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
//         return (builtin_cd(args, &env_list));
//     else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
//         return (builtin_pwd());
//     else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
//         return (builtin_export(args, &env_list));
//     else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
//         return (builtin_unset(args, &env_list));
//     else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
//         return (builtin_env(env_list));
//     else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
//         return (builtin_exit(args));
//     else
//         return (-1); // Retourne -1 si ce n'est pas un builtin
// }