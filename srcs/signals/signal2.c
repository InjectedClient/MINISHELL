/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:49:27 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/16 17:20:26 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Gestionnaire de signal pour CTRL-C (SIGINT) utilisé dans un contexte général
 * du programme. Cette fonction définit la réponse du programme à
 * l'interruption par CTRL-C, typiquement utilisée pour interrompre des
 * opérations en cours et réinitialiser l'interface utilisateur.
 */
void	ctrl_c_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global = 130;
}

/**
 * Gestionnaire de signal pour le signal CTRL-C (SIGINT) spécifique au contexte
 * des 'here documents'. Cette fonction définit la manière dont le programme
 * doit réagir lorsque CTRL-C est pressé pendant la lecture d'un
 * 'here document'.
 */
void	ctrl_c_handler_here_doc(int sig)
{
	(void)sig;
	close(0);
	printf("\n");
	g_global = 130;
}

/**
 * Configure les gestionnaires de signaux pour différents contextes d'exécution
 * dans le programme. Cette fonction ajuste la réponse du programme aux signaux
 * CTRL-C (SIGINT) et CTRL-Backslash (SIGQUIT) en fonction de l'état actuel,
 * particulièrement en ce qui concerne le traitement des 'here documents'.
 */
void	handle_sig(void)
{
		signal(CTRL_C_SIGINT, &ctrl_c_handler);
		signal(CTRL_BACKSLSH, IGNORE_SIG_ACTION);
}
