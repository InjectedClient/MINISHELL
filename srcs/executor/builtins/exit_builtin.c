/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:38:30 by jle-neze          #+#    #+#             */
/*   Updated: 2025/01/17 16:36:53 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

#include <limits.h> // Pour LONG_MAX et LONG_MIN

int	is_numeric(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result < 0)
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		str++;
	}
	return (result * sign);
}

int	builtin_exit(char **args)
{
	long	exit_code;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (is_numeric(args[1]))
	{
		exit_code = ft_atol(args[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = (unsigned char)exit_code;
		if (args[2])
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		exit(exit_code);
	}
	else
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(100);
	}
	return (0);
}
