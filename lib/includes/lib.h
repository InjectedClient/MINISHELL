/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:05:51 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/09 17:28:18 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <fcntl.h>
# include <stdlib.h>
# include "../../include/minishell.h"

int		ft_white_space(char c);
int		ft_is_space(char *str, char c);

#endif
