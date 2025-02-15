/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:39:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 15:06:16 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_2(char *var1, char *var2)
{
	if (var1)
		free(var1);
	if (var2)
		free(var2);
}

void	free_3(char *var1, char *var2, char *var3)
{
	if (var1)
		free(var1);
	if (var2)
		free(var2);
	if (var3)
		free(var3);
}

void	free_4(char *var1, char *var2, char *var3, char *var4)
{
	if (var1)
		free(var1);
	if (var2)
		free(var2);
	if (var3)
		free(var3);
	if (var4)
		free(var4);
}

void	free_3_env(char *var1, char *var2, t_env *var3)
{
	if (var1)
		free(var1);
	if (var2)
		free(var2);
	if (var3)
		free(var3);
}

void free_data(t_data *data)
{
    if (data->lexer_list)
	{
        free_lexer_list(data->lexer_list);
        data->lexer_list = NULL;
    }
    if (data->commands)
	{
        free_commands(data->commands);
        data->commands = NULL;
    }
	if (data->num_commands)
	{
        free(data->num_commands);
        data->num_commands = NULL;
    }
    if (data->input_cmd)
	{
        free(data->input_cmd);
        data->input_cmd = NULL;
    }
    if (data->args)
	{
        free_args(data->args);
        data->args = NULL;
    }
}