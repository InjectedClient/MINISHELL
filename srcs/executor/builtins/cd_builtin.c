#include "../../../include/minishell.h"

int error_cd()
{
    perror("minishell: cd");
    return (1);
}

int builtin_cd(char **args, t_env **env_list)
{
    char *path;
    char    *pwd;
    char cwd[1024];
    t_env   *current;

    if (args[2])
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    if (!args[1])
    {
        if (!(path = getenv("HOME")))
        {
            write(2, "minishell: cd: HOME not set\n", 28);
            return (1);
        }
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        current = *env_list;
        while (current)
        {
            if (ft_strcmp(current->name, "OLDPWD") == 0)
                path = current->value;
            current = current->next;
        }
        if (!path)
        {
            write(2, "minishell: cd: OLDPWD not set\n", 30);
            return (1);
        }
        printf("%s\n", path);
    }
    else
        path = args[1];
    // if (access(path, F_OK) != 0)
    //     error_cd();
    if (!getcwd(cwd, sizeof(cwd)))
        error_cd();
    if(!(pwd = ft_strjoin("OLDPWD=", cwd)))
    {
        write(2, "minishell: cd: memory allocation error\n", 40);
        return (1);
    }
    update_or_add_env(env_list, pwd);
    free(pwd);
    if (chdir(path) != 0)
        error_cd();
    if (!getcwd(cwd, sizeof(cwd)))
        error_cd();
    if(!(pwd = ft_strjoin("PWD=", cwd)))
    {
        write(2, "minishell: cd: memory allocation error\n", 40);
        return (1);
    }
    update_or_add_env(env_list, pwd);
    free(pwd);
    return (0);
}
