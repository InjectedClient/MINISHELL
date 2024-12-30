#include "../include/minishell.h"

int is_builtin(char *cmd)
{
    int i;
    char *builtins[] = {"cd", "env", "echo", "exit", "pwd", "export", "unset", NULL};

    i = 0;
    while (builtins[i])
    {
        if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
            return (1);
        i++;
    }
    return (0); // Retourne 0 si ce n'est pas un builtin
}

int exec_builtins(char **args, t_env *env_list) 
{
    if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
        return (builtin_echo(args));
    else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
        return (builtin_cd(args));
    else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
        return (builtin_pwd());
    else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
        return (builtin_export(args, env_list));
    else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
        return (builtin_unset(args, env_list));
    else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
        return (builtin_env(env_list));
    else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
        return (builtin_exit(args));
    else
        return (-1); // Retourne -1 si ce n'est pas un builtin
}

int    exec_cmd(char **cmd, char *envp[])
{
    int status;
    char    *path_var;
    char    *path;
    pid_t   pid;

    path_var = getenv("PATH");
    if (!path_var)
        return (cmd_not_found());
    path = get_cmd_path(cmd[0], path_var);
    if (!path)
        return (cmd_not_found());
    pid = fork();
    if (pid < 0)
        return (fork_error());
    if (pid == 0)
    {
        if (execve(path, cmd, envp) == -1)
            exit(cmd_not_exec());
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

int    exec(char *cmd[], t_env *env_list, char **envp)
{
    if (is_builtin(cmd[0]))
        g_global = exec_builtins(cmd, env_list);
    else
        g_global = exec_cmd(cmd, envp);
    
    return (0);
}

int count_args(t_lexer *arg)
{
    int count;

    count = 0;
    while (arg && arg->token == ARG)
    {
        count++;
        arg = arg->next;
    }
    return (count);
}

char    **split_args(t_lexer *cmd)
{
    char    **args;
    int num_args;
    int i;

    num_args = 0;
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
        free_tab(args);
        return (NULL);
    }
    i = 1;
    if (!num_args)
        args[i] = NULL;
    else
    {
        cmd = cmd->next;
        while (cmd && cmd->token == ARG)
        {
            args[i] = ft_strdup(cmd->cmd_segment);
            if (!args[i]) // Si une allocation échoue
            {
                free_tab(args);
                return (NULL);
            }
            cmd = cmd->next;
            i++;
        }
        args[i] = NULL;
    }
    return (args);
}

int execute_token(t_data data, t_env *env_list, char **envp)
{
    t_lexer *current;
    int fd_in;
    int fd_out;
    // int stdin_save = dup(STDIN_FILENO);
    // int stdout_save = dup(STDOUT_FILENO); 
    // int p_fd[2];
    // pid_t   pid;
    char **args;

    fd_in = 0;
    fd_out = 1;
    current = data.lexer_list;
    while (current)
    {
        if (current->token == CMD)
        {
            args = split_args(current); //TODO PLSU MALLOC
            if (!args)
                return (1);
        }

        if (current->token == REDIRECT_IN)
        {
            fd_in = open(current->next->cmd_segment, O_RDONLY);
            if (fd_in == -1)
            {
                perror("file");
                return (1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
            current = current->next;
        }

        if (current->token == REDIRECT_OUT)
        {
            fd_out = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC);
            if (fd_out == -1)
            {
                perror("file");
                return (1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
            current = current->next;
        }
        current = current->next;
    }
    // Une fois les redirections configurées, exécuter la commande
    if (args)
    {
        if (exec(args, env_list, envp) == -1) {
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