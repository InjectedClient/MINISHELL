#include "executor.h"
#include "types.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



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

int count_args(t_lexer *arg)
{
    int count;

    count = 0;
    while (arg->token == ARG)
    {
        count++;
        arg = arg->next;
    }
    printf("jsute apres cout args\n");
    return (count);
}

char    **split_args(t_lexer *cmd)
{
    char    **args;
    int num_args;
    int i;

    printf("debut de splitargs\n");
    num_args = 0;
    if (!cmd || !cmd->cmd_segment)
    {
        fprintf(stderr, "Error: invalid command or arguments.\n");
        return NULL;
    }
    if (cmd->next && cmd->next->token == ARG)
        num_args = count_args(cmd->next);
    args = malloc(sizeof(char *) * (num_args + 2)); //Pour caracter null plus la cmd
    if (!args)
    {
        perror("malloc");
        return (NULL);
    }
    args[0] = ft_strdup(cmd->cmd_segment);
    if (!args[0])
    {
        perror("malloc");
        free(args);
        return (NULL);
    }
    if (!num_args)
    {
        args[1] = NULL;
        return (args);
    }
    cmd = cmd->next;
    i = 1;
    while (cmd && cmd->token == ARG)
    {
        args[i] = ft_strdup(cmd->cmd_segment);
        if (!args[i]) // Si une allocation échoue
        {
            perror("ft_strdup");
            while (i > 0) // Libérer les arguments déjà alloués
                free(args[--i]);
            free(args);
            return (NULL);
        }
        cmd = cmd->next;
        i++;
    }
    args[i] = NULL;
    return (args);
}

int execute_token(t_data data, char *envp[])
{
    t_lexer *current;
    // int fd_in;
    // int fd_out;
    // int stdin_save = dup(STDIN_FILENO);
    // int stdout_save = dup(STDOUT_FILENO); 
    // int p_fd[2];
    // pid_t   pid;
    char **args;

    // fd_in = 0;
    // fd_out = 1;
    current = data.lexer_list;
    while (current)
    {
        if (current->token == CMD)
        {
            printf("avantsplitargs\n");
            args = split_args(current); //TODO PLSU MALLOC
            if (!args)
                return (1);
        }

        // if (current->token == REDIRECT_IN)
        // {
        //     fd_in = open(current->next->cmd_segment, O_RDONLY);
        //     if (fd_in == -1)
        //     {
        //         perror("file");
        //         return (1);
        //     }
        //     dup2(fd_in, STDIN_FILENO);
        //     close(fd_in);
        //     current = current->next;
        // }

        // if (current->token == REDIRECT_OUT)
        // {
        //     fd_out = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC);
        //     if (fd_out == -1)
        //     {
        //         perror("file");
        //         return (1);
        //     }
        //     dup2(fd_out, STDOUT_FILENO);
        //     close(fd_out);
        //     current = current->next;
        // }
        current = current->next;
    }
    // Une fois les redirections configurées, exécuter la commande
    if (args)
    {
        if (exec(args, envp) == -1) {
            perror("exec error");
            return (1);
        }

        // Libérer les arguments après exécution
        for (int i = 0; args[i]; i++) free(args[i]);
        free(args);
    }

    // Restaurer les descripteurs d'origine
    // dup2(stdin_save, STDIN_FILENO);
    // dup2(stdout_save, STDOUT_FILENO);
    // close(stdin_save);
    // close(stdout_save);

    return (0);
}




int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {"cd", "env", "echo", "exit", NULL};

    i = 0;
    while (builtins[i])
    {
        if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
            return (1);
        i++;
    }
    return (0); // Retourne 0 si ce n'est pas un builtin
}

int exec_builtin(char **args, char *envp[]) 
{
    if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
        return (builtin_echo(args));
    else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
        return (builtin_cd(args));
    else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
        return (builtin_pwd());
    // else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
    //     return (builtin_export());
    // else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
    //     return (builtin_unset(args));
    else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
        return (builtin_env(envp));
    else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
        return (builtin_exit(args));
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
