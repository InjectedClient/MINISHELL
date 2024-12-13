#include "../include/minishell.h"

unsigned int g_global = 0;

int main(int argc, char **argv, char *envp[])
{
	char *tmp;

	t_data data;
	(void)envp;
	if (argc != 1)
		return (printf("wrong number of args"), 0);
	init_data(&data, argc, argv);
	while (1)
	{
		int g_global;
		tmp = NULL;
		//call_sig(argc);
		tmp = readline("minishell$ ");
		add_history(tmp);
		looping(tmp, &data, envp);
	}
}

