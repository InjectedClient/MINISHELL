#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <stdlib.h>
#include <unistd.h>    // fork, execve
#include <sys/wait.h>  // wait, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
# include <sys/wait.h>
# include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h> // Pour NULL

#include "utils.h"
#include "errors.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main
int     exec(char *cmd[], char *envp[]);
int     exec_cmd(char *cmd[], char *path, char *envp[]);

//Path
char    *get_cmd_path(char *cmd);


int exec_builtin(char **args, char *envp[]);
int is_builtin(char *cmd);

int     builtin_echo(char **args);
int     builtin_cd(char **args);
int     builtin_env(char *envp[]);
int     builtin_pwd();


int     builtin_exit(char **args);

//Pipe
#endif