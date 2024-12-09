/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:56:30 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/05 15:57:34 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Vérifie si seul le guillemet simple est activé.
 */
int is_only_single_quote_on(t_quote *state)
{
	return (state->doubl_quot_status == 0 && state->singl_quot_status == 1);
}

/**
 * Réinitialise l'état des guillemets.
 */
void reset_quoting_state(t_quote *state)
{
	state->doubl_quot_status = 0;
	state->singl_quot_status = 0;
}
