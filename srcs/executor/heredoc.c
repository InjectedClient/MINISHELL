/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/17 19:13:44 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc_2(char *delimiter, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_global == 130)
		{
			if (g_global == 130)
			{
				free(line);
				break ;
			}
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
}

int	handle_all_heredocs(t_lexer *command, int *infile)
{
	int		tmp_fd;
	char	*delimiter;
	t_lexer	*current;

	signals_heredoc();
	tmp_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror("open heredoc_tmp");
		return (1);
	}
	current = command;
	while (current)
	{
		if (current->token == HERE_DOC)
		{
			delimiter = current->next->cmd_segment;
			handle_heredoc_2(delimiter, tmp_fd);
		}
		current = current->next;
	}
	close(tmp_fd);
	*infile = open("heredoc_tmp", O_RDONLY);
	if (*infile == -1)
	{
		perror("open heredoc_tmp for reading");
		return (1);
	}
	unlink("heredoc_tmp");
	return (0);
}
