/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:30:19 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/12 15:33:56 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// Fonction pour compter le nombre d'éléments dans la liste chaînée
int count_lexer_list(t_lexer *head)
{
	int count = 0;
	t_lexer *current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

// Fonction pour convertir la liste chaînée en tableau
char **convert_list_to_array(t_lexer *head)
{
	int count = count_lexer_list(head);
	char **array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return NULL;

	t_lexer *current = head;
	int i = 0;
	while (i < count)
	{
		array[i] = current->cmd_segment;
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return array;
}

