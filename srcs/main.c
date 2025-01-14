/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:39:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/14 15:28:20 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	g_global = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_data	data;
	t_env	*env_list;
	char	*tmp;

	(void)envp;
	if (argc != 1)
		return (printf("wrong number of args"), 0);
	init_data(&data, argc, argv);
	env_list = init_env_list(envp);
	while (1)
	{
		tmp = NULL;
		signals_wait_cmd();
		tmp = readline("minishell$ ");
		signals_run_cmd();
		add_history(tmp);
		looping(tmp, &data, env_list, envp);
	}
}
