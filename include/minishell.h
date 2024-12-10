/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:17:31 by nlambert          #+#    #+#             */
/*   Updated: 2024/12/09 17:27:38 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINISHELL_H
#define MINISHELL_H


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━ LIB ━━━━━━━━━━━━━━━━━━━━━━━━━━*/

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../lib/includes/lib.h"

# define SHIFT_OUT 14 // SO (Shift Out)

#	endif
