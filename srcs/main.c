#include "../include/minishell.h"

int main(int argc, char **argv, char *envp[]) //TODO Ajout env
{
	if (argc != 1)
		return (printf("wrong number of args"), 0);
	get_input(argc, argv, envp);
}

void get_input(int argc, char **argv, char *envp[])
{
	char *tmp;
	t_data data;

	init_data(&data, argc, argv);
	while (1)
	{
		tmp = NULL;
		// Affiche le prompt et lit l'entrée de l'utilisateur
		tmp = readline("minishell$ ");
		// Ajoute la commande à l'historique
		add_history(tmp);
		// Traite la commande entrée par l'utilisateur
		looping(tmp, &data, envp);
	}
}
