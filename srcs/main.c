/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:39:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/10 14:19:21 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	g_global = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;
	t_env	*env_list;
	char	*tmp;

	(void)argv;
	if (argc != 1)
		return (printf("wrong number of args"), 0);
	if (!envp || !*envp)
	{
		printf("No environment found\n");
		return (0);
	}
	env_list = init_env_list(envp);
	data.env_list = env_list;
	while (1)
	{
		tmp = NULL;
		signals_wait_cmd();
		tmp = readline("minishell$ ");
		signals_run_cmd();
		add_history(tmp);
		looping(tmp, &data, env_list);
	}
}
