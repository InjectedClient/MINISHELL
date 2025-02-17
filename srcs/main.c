/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:39:02 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/11 14:30:25 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned int	g_global = 0;

void	update_env_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;
	char	*shlvl_update;

	shlvl_str = ft_getenv("SHLVL", *env_list);
	shlvl = 1;
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	new_shlvl = ft_itoa(shlvl);
	shlvl_update = ft_strjoin("SHLVL=", new_shlvl);
	update_or_add_env(env_list, shlvl_update);
	free(new_shlvl);
	free(shlvl_update);
}

void	init_data(t_data *data)
{
	data->input_cmd = NULL;
	data->lexer_list = NULL;
	data->commands = NULL;
	data->num_commands = 0;
	data->is_sing_quot = 0;
	data->is_doub_quot = 0;
}

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
	update_env_shlvl(&env_list);
	while (1)
	{
		tmp = NULL;
		signals_wait_cmd();
		tmp = readline("minishell$ ");
		signals_run_cmd();
		add_history(tmp);
		init_data(&data);
		looping(tmp, &data, env_list);
		free_data(&data);
		free(tmp);
	}
}
