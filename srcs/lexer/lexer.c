/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:12 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 15:10:28 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Ajoute un nouvel élément lexer à la fin de la liste chaînée lexer_list.
 * Si la liste est vide, initialise la liste avec le nouvel élément.
 * CHECK SI CETTE FONCTION EST UTILISEE
 */
int	add_lexer_to_end(t_data *data, char *str)
{
	t_lexer	*new;
	t_lexer	*current;

	new = create_new_lexer(str);
	if (!new)
		return (0);
	if (data->lexer_list == NULL)
	{
		data->lexer_list = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		current = data->lexer_list;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
	return (1);
}

/**
 * Crée un nouvel élément lexer avec le segment de commande donné.
 * Initialise les pointeurs next et prev à NULL.
 */
t_lexer	*create_new_lexer(char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->cmd_segment = str;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * Met à jour les positions des segments dans la liste lexer_list.
 * La position est réinitialisée à 0 après chaque opérateur de pipe '|'.
 */
void	get_data_in_node(t_lexer **lexer_list)
{
	t_lexer	*tmp;
	int		i;
	int		y;

	i = 1;
	y = 0;
	tmp = *lexer_list;
	while (tmp)
	{
		if (tmp->cmd_segment[0] == '|')
		{
			i = 0;
			y++;
		}
		tmp->segment_position = i;
		tmp = tmp->next;
		i++;
	}
}
