
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
        return (builtin_cd(args, &env_list));
    else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
        return (builtin_pwd());
    else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
        return (builtin_export(args, &env_list));
    else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
        return (builtin_unset(args, &env_list));
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

int    exec_cmd_2(char **cmd, char *envp[])
{
    char    *path_var;
    char    *path;

    path_var = getenv("PATH");
    if (!path_var)
        return (cmd_not_found());
    path = get_cmd_path(cmd[0], path_var);
    if (!path)
        return (cmd_not_found());
    if (execve(path, cmd, envp) == -1)
            exit(cmd_not_exec());
    return (0);
}

int    exec(char *cmd[], t_env *env_list, char **envp, int fork)
{
    if (is_builtin(cmd[0]))
        g_global = exec_builtins(cmd, env_list);
    else
    {
        if (fork)
            g_global = exec_cmd(cmd, envp);
        else
            g_global = exec_cmd_2(cmd, envp);
    }
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
    if (cmd->token == CMD)
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


int execute_token(t_data *data, t_env *env_list, char **envp)
{
    t_lexer *current;
    int fd_in;
    int fd_out;
    int prev_fd;
    pid_t   pid;
    int pipe_fd[2] ={-1, -1};
    int stdin_save = dup(STDIN_FILENO);
    int stdout_save = dup(STDOUT_FILENO); 
    char **args;

    prev_fd = -1;
    current = data->lexer_list;
    while (current)
    {
        fd_in = -1;
        fd_out = -1;

        if (current->token == CMD)
        {
            args = split_args(current);
            if (!args)
                return (1);
        }
        if (current->token == REDIRECT_OUT) 
        {
            if (current->next && current->next->cmd_segment) 
                fd_out = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1) 
            {
                perror("Erreur d'ouverture du fichier (>)");
                return -1;
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        if (current->token == REDIRECT_IN) 
        {
            if (current->next && current->next->cmd_segment)
            {
                fd_in = open(current->next->cmd_segment, O_RDONLY);
            if (fd_in == -1)
            {
                perror("Erreur d'ouverture du fichier (<)");
                return -1;
            }
            dup2(fd_in, STDIN_FILENO);
            }
        }
        if (current->token == APPEND_OUT) 
        {
            if (current->next && current->next->cmd_segment) 
                fd_out = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out == -1) 
            {
                perror("Erreur d'ouverture du fichier (>)");
                return -1;
            }
            dup2(fd_out, STDOUT_FILENO);
        }
        if (current->token == PIPE)
        {
            // Créer un pipe pour la commande suivante
            if (pipe(pipe_fd) == -1)
            {
                perror("Erreur de création du pipe");
                return (1);
            }
            // Fork pour exécuter la commande
            pid = fork();
            if (pid == -1)
            {
                perror("Erreur de fork");
                return (1);
            }
            if (pid == 0)
            { // Processus enfant
                // Redirection de l'entrée
                if (fd_in != -1)
                {
                    dup2(fd_in, STDIN_FILENO);
                    close(fd_in);
                }
                else if (prev_fd != -1)
                {
                    dup2(prev_fd, STDIN_FILENO);
                }

                // Redirection de la sortie
                if (fd_out != -1)
                {
                    dup2(fd_out, STDOUT_FILENO);
                    close(fd_out);
                } 
                else if (pipe_fd[1] != -1)
                { // Pipe suivant
                    dup2(pipe_fd[1], STDOUT_FILENO);
                }

                // Fermer tous les descripteurs inutiles
                close(pipe_fd[0]);
                close(pipe_fd[1]);

                // Exécuter la commande
                exec(args, env_list, envp, 0);
                perror("Erreur d'exécution");
                exit(1);
            }
            else
            { // Processus parent
                // Fermer les extrémités inutiles
                 int status;
                wait(&status);
                if (fd_in != -1) close(fd_in);
                if (fd_out != -1) close(fd_out);
                if (prev_fd != -1) close(prev_fd);
                if (pipe_fd[1] != -1) close(pipe_fd[1]);
                dup2(stdin_save, STDIN_FILENO);
                dup2(stdout_save, STDOUT_FILENO);

                // Met à jour prev_fd pour la prochaine commande
                prev_fd = pipe_fd[0];
            }
        }
        
        current = current->next;
    }
    //if (!current && args) //cas ou il y apas de pipe
    // init_fd(fd_in, fd_out, prev_fd, pipe_fd);
    if (args)
    {
        if (fd_in == -1 && prev_fd != -1)
            dup2(prev_fd, STDIN_FILENO);
        // if (fd_out == -1)
        //     dup2(stdout_save, STDOUT_FILENO);
        exec(args, env_list, envp, 1);
        free_tab(args);
    }
    dup2(stdin_save, STDIN_FILENO);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdin_save);
    close(stdout_save);
    while (wait(NULL) > 0);

    return (0);

    // if (current && current->token == PIPE)
    // {
    //     if (pipe(pipe_fd) == -1)
    //     {
    //         perror("minishell: pipe");
    //         return (1);
    //     }
    //     pid = fork();
    //     if (pid == -1)
    //     {
    //         perror("fork");
    //         return (1);
    //     }
    //     if (pid == 0)
    //     {
    //         init_fd(fd_in, fd_out, prev_fd, pipe_fd);
    //         exec(args, env_list, envp, 0);
    //         perror("exec error");
    //         exit(1);
    //     }
    // }
    // // Parent : Fermer les descripteurs inutiles
    // close_fd(fd_in, fd_out, prev_fd, pipe_fd);
    // // Met à jour prev_fd pour le prochain segment
    // prev_fd = pipe_fd[0];
}

    // Attend tous les processus enfants
    // while (wait(NULL) > 0);

    // Une fois les redirections configurées, exécuter la commande

    // Restaurer les descripteurs d'origine
    // dup2(stdin_save, STDIN_FILENO);
    // dup2(stdout_save, STDOUT_FILENO);
    // close(stdin_save);
    // close(stdout_save);
