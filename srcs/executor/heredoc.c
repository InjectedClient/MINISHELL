/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/13 11:41:53 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_heredoc(t_lexer *command, int *infile, t_lexer **redirection_start)
{
	t_lexer	*current;
	int		heredoc_found;

	current = command;
	heredoc_found = 0;
	while (current)
	{
		if (current->token == HERE_DOC)
		{
			heredoc_found = 1;
			break ;
		}
		current = current->next;
	}
	if (heredoc_found)
	{
		if ((handle_all_heredocs(command, infile)))
			return (1);
		dup2(*infile, STDIN_FILENO);
		close(*infile);
		*infile = STDIN_FILENO;
	}
	*redirection_start = current;
	return (0);
}

void	handle_heredoc_2(char *delimiter, int tmp_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
}

static void	process_heredocs(t_lexer *cmd, int fd)
{
	while (cmd)
	{
		if (cmd->token == HERE_DOC)
			handle_heredoc_2(cmd->next->cmd_segment, fd);
		cmd = cmd->next;
	}
}

int	handle_all_heredocs(t_lexer *command, int *infile)
{
	int	tmp_fd;

	tmp_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror("open heredoc_tmp");
		return (1);
	}
	process_heredocs(command, tmp_fd);
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
