#include "../../include/minishell.h"

void free_2(char *var1, char *var2)
{
    if (var1)
        free(var1);
    if (var2)
        free(var2);
}

void free_3(char *var1, char *var2, char *var3)
{
    if (var1)
        free(var1);
    if (var2)
        free(var2);
    if (var3)
        free(var3);
}

void free_4(char *var1, char *var2, char *var3, char *var4)
{
    if (var1)
        free(var1);
    if (var2)
        free(var2);
    if (var3)
        free(var3);
    if (var4)
        free(var4);
}


