/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:01:57 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 17:40:27 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_global = 130;
	write(1, "\n", 1);
	close(0);
}

void	signals_heredoc(void)
{
	signal(SIGINT, &handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
