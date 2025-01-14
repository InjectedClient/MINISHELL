/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:15 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/14 16:54:55 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Met à jour l'état des guillemets en fonction du caractère actuel.
 */
void	update_quoting_state(char c, t_quote *state)
{
	if (c == '\'')
	{
		if (is_single_quote_closed(state))
			state->singl_quot_status = 1;
		else
		{
			state->singl_quot_start_status = 0;
			state->singl_quot_status = 0;
		}
	}
	else if (c == '"')
	{
		if (is_doubl_quote_closed(state))
			state->doubl_quot_status = 1;
		else
			state->doubl_quot_status = 0;
	}
	if (is_only_single_quote_on(state))
		state->singl_quot_start_status = 1;
}

/**
 * Vérifie si le guillemet simple est ouvert.
 */
int	is_single_quote_open(t_quote *state)
{
	return (state->singl_quot_status == 1);
}

/**
 * Vérifie si le guillemet simple est fermé.
 */
int	is_single_quote_closed(t_quote *state)
{
	return (state->singl_quot_status == 0);
}

/**
 * Vérifie si le guillemet double est ouvert.
 */
int	is_doubl_quote_open(t_quote *state)
{
	return (state->doubl_quot_status == 1);
}

/**
 * Vérifie si le guillemet double est fermé.
 */
int	is_doubl_quote_closed(t_quote *state)
{
	return (state->doubl_quot_status == 0);
}
