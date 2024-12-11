#include "minishell.h"

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
		int g_global;
		tmp = NULL;
		tmp = readline("minishell$ ");
		add_history(tmp);
		// TODO fonction is_command pour les cas ou meme pipe
		input = looping(tmp, &data);
		int i = -1;
		while (input[++i])
			printf("Linput est %s\n", input[i]);
		// TODO les fonctions en dessous avec un return du status pq pas
		g_global = exec(input, envp);
		printf("La varaible globale est \t%d\n", g_global);
	}
}

