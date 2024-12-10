/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:57:04 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/10 14:40:22 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Cette fonction est un gestionnaire pour le signal SIGINT (généralement envoyé lorsque l'utilisateur appuie sur Ctrl+C)
*/
void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_global = 130;
}
/*
 * Cette fonction est un gestionnaire pour le signal SIGQUIT (généralement envoyé lorsque l'utilisateur appuie sur Ctrl+)
*/
void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	g_global = 131;
	write(2, "Quit\n", 5);
}

/*
 * Configure les gestionnaires de signaux pour le processus en cours. Cette
 * fonction est essentielle dans des applications interactives comme les shells
 * ou  les éditeurs de texte pour personnaliser la réponse aux interruptions et
 * terminaisons.
*/
void	handle_signal(void)
{
	signal(SIGINT, &handle_ctrl_c);
	signal(SIGQUIT, &handle_ctrl_backslash);
}
