/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:57:04 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/09 15:16:51 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_global = 130;
}

void	handle_signal(void)
{
	signal(SIGINT, &handle_ctrl_c);
}
