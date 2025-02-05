/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 17:31:52 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_doc_read(int temp_fd, const char *delimiter)
{
	char	*line;

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
	return ;
}

int	generate_temp_filename(char *buffer, size_t buffer_size, int counter)
{
	char	*counter_str;
	size_t	prefix_len;
	int		i;

	i = 0;
	counter_str = malloc(12);
	if (!counter_str)
		return (-1);
	strcpy(buffer, "/tmp/minishell_heredoc_");
	prefix_len = strlen(buffer);
	while (counter > 0)
	{
		counter_str[i++] = '0' + (counter % 10);
		counter /= 10;
	}
	counter_str[i] = '\0';
	if (prefix_len + strlen(counter_str) + 1 > buffer_size)
	{
		free(counter_str);
		return (-1);
	}
	strcat(buffer, counter_str);
	free(counter_str);
	return (0);
}

int	handle_here_doc(const char *delimiter)
{
	static int	counter;
	char		temp_file[256];
	int			temp_fd;

	counter = 0;
	if (generate_temp_filename(temp_file, sizeof(temp_file), counter) == -1)
		return (-1);
	counter++;
	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	here_doc_read(temp_fd, delimiter);
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

int	handle_here_doc_token(t_lexer *current, int *infile)
{
	signals_heredoc();
	*infile = handle_here_doc(current->next->cmd_segment);
	if (*infile == -1)
	{
		perror("heredoc");
		return (1);
	}
	dup2(*infile, STDIN_FILENO);
	signals_wait_cmd();
	signals_run_cmd();
	return (0);
}
