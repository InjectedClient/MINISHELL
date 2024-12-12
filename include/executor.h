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

//Builtins
typedef struct {
    char *name;                       // Nom du builtin
    int (*function)(char **args);     // Pointeur vers la fonction du builtin
} builtin_t;

int exec_builtin(char **args);
int is_builtin(char *cmd);

int builtin_cd(char **args);
int builtin_env(char **args);
int builtin_echo(char **args);

//Pipe
#endif