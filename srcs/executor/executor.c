#include "../../include/minishell.h"

char    *get_path_from_env(char *name, char *envp[])
{
    int i;
    int len;

    len = ft_strlen(name);
    i = -1;
    while (envp[++i])
    {
        if (ft_strncmp(name, envp[i], len) == 0 && envp[i][len] == '=')
        {
            return (envp[i] + len + 1);
        }
    }
    return (NULL);
}

char    *get_cmd_path(char *cmd, char *envp[])
{
    int i;
    char    *exec;
    char    **path;
    char    *path_part;

    path = malloc_check(ft_split(get_path_from_env("PATH", envp), ':')); // Les paths sont separe par des : ex: PATH=/truc/truc:home/bin/:/blabla on les separ
    i = -1;
    while (path[++i])
    {
        if (!(path_part = ft_strjoin(path[i], "/"))) // On ajoute un / derriere le path part ex : /truc/truc --> /truc/truc/
            free_tab_and_exit(path);
        exec = ft_strjoin(path_part, cmd); // On ajoute la commande derriere ex: /truc/truc/ --> /truc/truc/cat
        free(path_part);
        if (!exec)
            free_tab_and_exit(path);
        if (access(exec, F_OK | X_OK) == 0)
        {
            free_array(path);
            return (exec);
        }
        free(exec);
    }
    free_array(path);
    return(NULL);
}



void    exec(char *cmd[], char *envp[])
{
    char    *path;

    if ((path = get_cmd_path(cmd[0], envp)))
        exec_cmd(cmd, path, envp);
    if (is_builtin(cmd))
        exec_builtins(cmd);
}

void    exec_cmd(char *cmd[], char *path, char *envp[])
{
    int status;
    pid_t   pid;

    pid = fork();
    if (pid < 0)
    {
        fork_error();
        return (-1);
    }
    if (pid == 0)
    {
        if (execve(path, cmd, envp) == -1)
            execve_error();
        exit(0);
    }
    else 
    {
        // Processus parent
        wait(&status); // Récupérer l'état de l'enfant
        if (WIFEXITED(status)) {
            return (WEXITSTATUS(status)); // Retourner le code de retour de la commande
        } else if (WIFSIGNALED(status)) {
            return (128 + WTERMSIG(status)); // Indiquer que l'enfant a été tué par un signal
        }
    }
    return (0);


}

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
