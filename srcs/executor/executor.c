
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

int    exec_cmd(char **cmd, char *envp[], t_env *env_list)
{
    int status;
    char    *path;
    pid_t   pid;

    if (access(cmd[0], X_OK) != -1)
    {
        path = ft_strdup(cmd[0]);
        if (!path)
            return (1);
    }
    else
    {
        path = get_cmd_path(cmd[0], env_list);
        if (!path)
            return (cmd_not_found());
    }
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

int    exec_cmd_2(char **cmd, char *envp[], t_env *env_list)
{
    char    *path;

    if (execve(cmd[0], cmd, envp) == -1)
    {
        path = get_cmd_path(cmd[0], env_list);
        if (!path)
            return (cmd_not_found());
        if (execve(path, cmd, envp) == -1)
                return (cmd_not_exec());
    }
    return (0);
}

int    exec(char *cmd[], t_env *env_list, char **envp, int fork)
{
    if (is_builtin(cmd[0]))
        g_global = exec_builtins(cmd, env_list);
    else
    {
        if (fork)
            g_global = exec_cmd(cmd, envp, env_list);
        else
            g_global = exec_cmd_2(cmd, envp, env_list);
    }
    return (g_global);
}


int handle_redirections(t_lexer *current, int fds[2])
{
    if (current->token == REDIRECT_OUT)
    {
        fds[1] = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fds[1] == -1)
        {
            perror("minishell");
            if (fds[0] != -1) // Nettoie les descripteurs précédents
                close(fds[0]);
            return (-1);
        }
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
    }
    else if (current->token == APPEND_OUT)
    {
        fds[1] = open(current->next->cmd_segment, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fds[1] == -1)
        {
            perror("minishell");
            if (fds[0] != -1)
                close(fds[0]);
            return (-1);
        }
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
    }
    else if (current->token == REDIRECT_IN)
    {
        fds[0] = open(current->next->cmd_segment, O_RDONLY);
        if (fds[0] == -1)
        {
            perror("minishell");
            return (-1);
        }
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
    }
    else if (current->token == HERE_DOC)
    {
        fds[0] = handle_here_doc(current->next->cmd_segment);
        if (fds[0] == -1)
        {
            perror("minishell");
            return (-1);
        }
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
    }
    return (0);
}


void cleanup(int fds[2], int prev_fd, int pipe_fd[2], char **args)
{
    if (fds[0] != -1)
        close(fds[0]);
    if (fds[1] != -1)
        close(fds[1]);
    if (prev_fd != -1)
        close(prev_fd);
    if (pipe_fd[0] != -1)
        close(pipe_fd[0]);
    if (pipe_fd[1] != -1)
        close(pipe_fd[1]);
    if (args)
        free_tab(args);
}

void execute_child(int fds[2], int pipe_fd[2], int prev_fd, char **args, t_env *env_list, char **envp)
{
    if (fds[0] != -1)
    {
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
    }
    else if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (fds[1] != -1)
    {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
    }
    else if (pipe_fd[1] != -1)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    exec(args, env_list, envp, 0);
    perror("minishell");
    exit(1);
}

int execute_token(t_data *data, t_env *env_list, char **envp)
{
    t_lexer *current;
    int fds[2]; // LE 0 est in et le 1 est out 
    int prev_fd;
    pid_t   pid;
    int pipe_fd[2] ={-1, -1};
    int stdin_save = dup(STDIN_FILENO);
    int stdout_save = dup(STDOUT_FILENO); 
    char **args = NULL;

    prev_fd = -1;
    current = data->lexer_list;
    while (current)
    {
        fds[0] = -1;
        fds[1] = -1;
        if (current->token == CMD)
        {
            args = split_args(current);
            if (!args)
                return (1);
        }
        if (current->token == REDIRECT_OUT || current->token == APPEND_OUT || current->token == REDIRECT_IN || current->token == HERE_DOC)
        {
            if (handle_redirections(current, fds) == -1)
            {
                cleanup(fds, prev_fd, pipe_fd, args);
                return (1);
            }
        }
        if (current->token == PIPE)
        {
            // Créer un pipe pour la commande suivante
            if (pipe(pipe_fd) == -1)
            {
                perror("minishell");
                return (1);
            }
            printf("\n\nLa valeur de fsd[0] est %d, La valeur de fsd[1] est %d, La valeur de pipe_fd[0] est %d, La valeur de pipe_fd[1] est %d la valeur de prev_fd est %d\n\n", fds[0], fds[1], pipe_fd[0], pipe_fd[1], prev_fd);
            // Fork pour exécuter la commande
            pid = fork();
            if (pid == -1)
            {
                perror("Erreur de fork");
                return (1);
            }
            if (pid == 0)
                execute_child(fds, pipe_fd, prev_fd, args, env_list, envp);
            else
            { // Processus parent
                // Fermer les extrémités inutiles
                int status;
                wait(&status);
                if (fds[0] != -1)
                    close(fds[0]);
                if (fds[1] != -1)
                    close(fds[1]);
                if (prev_fd != -1)
                    close(prev_fd);
                if (pipe_fd[1] != -1)
                    close(pipe_fd[1]);

                // Met à jour prev_fd pour la prochaine commande
                prev_fd = pipe_fd[0];
            }
        }
        
        current = current->next;
    }
    if (args)
    {
        if (fds[0] != -1)
            dup2(fds[0], STDIN_FILENO);
        else if (fds[0] == -1 && prev_fd != -1)
            dup2(prev_fd, STDIN_FILENO);
        exec(args, env_list, envp, 1);
    }
    dup2(stdin_save, STDIN_FILENO);
    dup2(stdout_save, STDOUT_FILENO);
    close(stdin_save);
    close(stdout_save);
    cleanup(fds, prev_fd, pipe_fd, args);
    while (wait(NULL) > 0);
    return (0);
}
