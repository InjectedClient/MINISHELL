/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:16:41 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:42 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pids(t_data *data, pid_t **pid)
{
	*pid = malloc((data->num_commands) * sizeof(pid_t));
	if (!*pid)
		return (0);
	return (1);
}

int	create_pipes(t_data *data, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * (data->num_commands - 1));
	if (!*pipes)
		return (0);
	i = 0;
	while (i < data->num_commands - 1)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i] || pipe((*pipes)[i]) == -1)
		{
			perror("pipe");
			while (i-- > 0)
			{
				close((*pipes)[i][0]);
				close((*pipes)[i][1]);
				free((*pipes)[i]);
			}
			free((*pipes));
			return (0);
		}
		i++;
	}
	return (1);
}

void	close_pipes(int **pipes, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
