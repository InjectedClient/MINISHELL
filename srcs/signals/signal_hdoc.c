/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:01:57 by nlambert          #+#    #+#             */
/*   Updated: 2025/02/17 19:07:30 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_sigint(int sig)
{
	char	eof;

	if (sig == SIGINT)
	{
		printf("\n");
		g_global = 130;
		rl_done = 1;
		eof = 4;
		ioctl(STDIN_FILENO, TIOCSTI, &eof);
	}
}

void	signals_heredoc(void)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
