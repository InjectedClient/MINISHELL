#include "../../include/minishell.h"

builtin_t builtins[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"echo", builtin_echo},
    {NULL, NULL},
};

int    exec(char *cmd[], char *envp[])
{
    char    *path;

    if (is_builtin(cmd[0]))
        return(exec_builtin(cmd, envp));
    if ((path = get_cmd_path(cmd[0])))
        return(exec_cmd(cmd, path, envp));
    else
        return (1);
}

int is_builtin(char *cmd)
{
    int i;

    i = 0;
    while (builtins[i].name)
    {
        if (ft_strncmp(cmd, builtins[i].name, ft_strlen(cmd)) == 0)
            return (1);
        i++;
    }
    return (0); // Retourne 0 si ce n'est pas un builtin
}

int exec_builtin(char **args, char *envp[])
{
    // int i;

    // i = 0;
    // while (builtins[i].name)
    // {
    //     if (ft_strncmp(args[0], builtins[i].name, ft_strlen(args[0])) == 0)
    //         return (builtins[i].function(args));
    //     i++;
    // }
    if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
        return (builtin_echo(args));
    else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
        return (builtin_cd(args));
    // else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
    //     return (builtin_pwd());
    // else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
    //     return (builtin_export());
    // else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
    //     return (builtin_unset(args));
    else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
        return (builtin_env(envp));
    // else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
    //     return (builtin_exit(args));
    else
        return (-1); // Retourne -1 si ce n'est pas un builtin
}

int    exec_cmd(char *cmd[], char *path, char *envp[])
{
    int status;
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        return (fork_error());
    if (pid == 0)
    {
        if (execve(path, cmd, envp) == -1)
            exit(execve_error());
    }
    else
    {
        wait(&status); // Récupérer l'état de l'enfant
        if (WIFEXITED(status))
            return (WEXITSTATUS(status)); // Retourner le code de retour de la commande
        else if (WIFSIGNALED(status))
            return (128 + WTERMSIG(status)); // Indiquer que l'enfant a été tué par un signal
    }
    return (1);
}

// int exec_builtins(cmd)
// {

// }

// int main(int argc, char *argv[], char *envp[])
// {
//     (void)argc;
//     (void)argv;
//     pid_t   pid;
//     char    *cmd[] = {"cat", "text.txt", NULL};

//     pid = fork();
//     if (pid == -1)
//     {
//         perror("pid erreur");
//         exit(1);
//     }
//     if (pid == 0) // On est dans le process enfant
//     {
//         exec(cmd, envp);
//     }
//     return (0);
// }

// int main(int argc, char *argv[], char *envp[])
// {
//     int i;

//     if (argc < 2)
//     {
//         perror("Usage: ./a.out <commande> [options...]\n"); // Par exemple ./a.out ls -a ou encore juste ./a.out ls ou ./a.out cat
//         return (EXIT_FAILURE);
//     }
//     char **cmd = malloc(sizeof(char *) * argc); // je les met dans un double tableau ducoup {"ls", "-l", ...}
//     if (!cmd)
//     {
//         perror("Erreur d'allocation mémoire");
//         return (EXIT_FAILURE);
//     }
//     i = 0;
//     while(i < argc - 1)
//     {
//         cmd[i] = argv[i + 1];
//         i++;
//     }
//     cmd[argc - 1] = NULL;
//     exec(cmd, envp);

//     perror("PROBLEME");
//     return (EXIT_SUCCESS);
// }
