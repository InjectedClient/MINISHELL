/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:16:25 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:26 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_saved_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		perror("minishell ");
		return (1);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror("minishell ");
		close(*saved_stdin);
		return (1);
	}
	return (0);
}

int	restore_and_close_saved_fds(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell ");
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell ");
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}
