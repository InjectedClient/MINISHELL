#include "../include/minishell.h"

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
		input = looping(tmp, &data, envp);
		if (is_cmd(input))
			exec(input);
		// ...
	}
}

void get_input(int argc, char **argv, char *envp[])
{
	
}
