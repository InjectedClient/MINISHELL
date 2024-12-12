#include "../include/minishell.h"

unsigned int g_global = 0;

int main(int argc, char **argv, char *envp[])
{
	char *tmp;
	char	**input;
	t_data data;

	if (argc != 1)
		return (printf("wrong number of args"), 0);
	init_data(&data, argc, argv);
	while (1)
	{
		tmp = NULL;
		tmp = readline("minishell$ ");
		add_history(tmp);
		// TODO fonction is_command pour les cas ou meme pipe
		input = looping(tmp, &data);
		// TODO les fonctions en dessous avec un return du status pq pas
		g_global = exec(input, envp);
	}
}

