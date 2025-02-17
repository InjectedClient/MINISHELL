/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:39:08 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/17 14:03:13 by nlambert         ###   ########.fr       */
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

int	free_word_and_state(char **word, t_quote **state)
{
	if (*word)
	{
		free(*word);
		*word = NULL;
	}
	if (*state)
	{
		free(*state);
		*state = NULL;
	}
	return (-1);
}
