#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <stdlib.h>
#include <unistd.h>    // fork, execve
#include <sys/wait.h>  // wait, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG
# include <sys/wait.h>
# include <unistd.h>

#include "errors.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main
int     exec(char *cmd[], char *envp[]);
int     exec_cmd(char *cmd[], char *path, char *envp[]);

//Path
char    *get_path_from_env(char *name, char *envp[]);
char    *get_cmd_path(char *cmd, char *envp[]);

//Builtins

//Pipe
#endif