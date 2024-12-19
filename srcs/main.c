#include "minishell.h"

int main(int argc, char **argv, char *envp[])
{
	char *tmp;
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
		// TODO les fonctions en dessous avec un return du status pq pas
		looping(tmp, &data);
		g_global = execute_token(data, envp);
		// t_lexer *tokens;
		// tokens = data.lexer_list;
		// while (tokens)
		// {
		// 	printf("segment_position: %i, cmd_segement: %s \n", tokens->segment_position, tokens->cmd_segment);
		// 	tokens = tokens->next;
		// }
		printf("La varaible globale est \t%d\n", g_global);
	}
}

