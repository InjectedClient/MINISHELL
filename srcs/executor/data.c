/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:15:28 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/30 16:15:29 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	**split_by_pipe(t_data *data)
{
	int		index;
	t_lexer	**commands;
	t_lexer	*current;
	t_lexer	*start;
	t_lexer *pipe_node;

	commands = malloc(sizeof(t_lexer *) * (data->num_commands + 1));
	if (!commands)
		return (NULL);
	index = 0;
	start = data->lexer_list;
	current = data->lexer_list;
    while (current)
    {
        if (current->token == PIPE)
        {
            pipe_node = current;
            if (pipe_node->prev)
                pipe_node->prev->next = NULL;
            commands[index++] = start;
            start = pipe_node->next;
            current = pipe_node->next;
            if (pipe_node->cmd_segment)
                free(pipe_node->cmd_segment);
            free(pipe_node);
            continue;
        }
        current = current->next;
    }
	commands[index] = start;
	commands[index + 1] = NULL;
	return (commands);
}

int	init_commands(t_data *data)
{
	data->commands = split_by_pipe(data);
	if (!data->commands)
		return (0);
	return (1);
}
