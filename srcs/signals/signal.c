/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:57:04 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/13 16:22:55 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_global = 130;
}
void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	g_global = 131;
	write(2, "Quit\n", 5);
}

void	handle_signal(void)
{
	signal(SIGINT, &handle_ctrl_c);
	signal(SIGQUIT, &handle_ctrl_backslash);
}

void	ctrl_c_handler(int sig)
{
	(void)sig;
	putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global = 130;
}

void	call_sig(int argc)
{
		(void)argc;
		signal(CTRL_C_SIGINT, &ctrl_c_handler);
		signal(CTRL_BACKSLSH, IGNORE_SIG_ACTION);
}

