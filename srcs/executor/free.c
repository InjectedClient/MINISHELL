/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:15:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:17 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_pipes(int num_commands, int ***pipes)
{
	int	i;

	if (!pipes || !*pipes)
		return ;
	i = 0;
	while (i < num_commands - 1)
	{
		if ((*pipes)[i])
		{
			close((*pipes)[i][0]);
			close((*pipes)[i][1]);
			free((*pipes)[i]);
		}
		i++;
	}
	free(*pipes);
	*pipes = NULL;
}

void	free_pids(pid_t **pids)
{
	if (*pids)
	{
		free(*pids);
		*pids = NULL;
	}
}
