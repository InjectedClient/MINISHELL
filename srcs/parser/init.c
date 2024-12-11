/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <jle-neze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:20:28 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/11 16:38:29 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "types.h"

void init_data(t_data *data, int argc, char **argv)
{
	data->command_count = argc;
	data->args = argv;
}


