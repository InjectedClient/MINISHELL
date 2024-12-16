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
		tmp = NULL;
		//sigal 2? probleme ctrl d + "\"
		handle_signal();
		tmp = readline("minishell$ ");
		add_history(tmp);
		looping(tmp, &data, envp);
	}
}

