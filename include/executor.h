#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <stdlib.h> // getenv
#include <unistd.h>    // fork, execve
#include <stdio.h> //perror
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
#include <fcntl.h> //open

#include "utils.h"
#include "errors.h"
#include "types.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main
int    exec_cmd(char **cmd, char *envp[]);
int     exec(char *cmd[], char *envp[]);
int     execute_token(t_data data, char *envp[]);

//Args
int     count_args(t_lexer *arg);
char    **split_args(t_lexer *cmd);

//Path
char    *get_cmd_path(char *cmd, char *path_var);

//Builtins
int     is_builtin(char *cmd);
int     exec_builtins(char **args, char *envp[]);

int     builtin_echo(char **args);
int     builtin_cd(char **args);
int     builtin_env(char *envp[]);
int     builtin_pwd();


int     builtin_exit(char **args);

//Pipe
#endif