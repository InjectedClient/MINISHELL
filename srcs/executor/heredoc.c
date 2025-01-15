/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 14:03:44 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_here_doc(const char *delimiter)
{
	static int	counter = 0;
	char		temp_file[256];
	char		*counter_str;
	char		*line;
	int			temp_fd;
	int			i;

	counter_str = malloc(12);
	strcpy(temp_file, "/tmp/minishell_heredoc_");
	if (!counter_str)
		return (-1);
	int			temp = counter;
	i = 0;
	while (temp > 0)
	{
		counter_str[i++] = '0' + (temp % 10);
		temp /= 10;
	}
	counter_str[i] = '\0';
	strcat(temp_file, counter_str);
	free(counter_str);
	counter++;
	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	close(temp_fd);
	temp_fd = open(temp_file, O_RDONLY);
	if (temp_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	unlink(temp_file);
	return (temp_fd);
}
