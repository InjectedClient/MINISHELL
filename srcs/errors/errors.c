/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:41:55 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 15:50:59 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error(void)
{
	perror("error_general");
	return (1);
}

int	malloc_error(void)
{
	perror("malloc");
	return (1);
}

int	fork_error(void)
{
	perror("fork");
	return (1);
}

int	cmd_not_exec(void)
{
	perror("command not executable");
	return (126);
}

int	cmd_not_found(void)
{
	perror("minishell ");
	return (127);
}
