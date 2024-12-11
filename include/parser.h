#ifndef PARSER_H
# define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void init_data(t_data *data, int argc, char **argv);
int	check_quotes(char *str, t_data *data);
int	check_redirections(char *str);
int	check_cmd_start(char *str);
int	check_redirection_arg(t_data *data);
int	check_invalid_pipes(t_data *data);
int	check_nb_redir(char *str);
int	check_token_error(t_data *data);
int	check_invalid_tokens(t_data *data);
int	check_invalid_tokens2(t_data *data);
int	check_slash(char *str, char c);
int	check_directory(char *str);
int	check_pipe_bracket(char *str);
int	ft_check_parser(t_data *data);
int	is_a_directory(t_data *data);

//char	*rm_single_quotes(t_data *data, char *tmp);
//char	*rm_double_quotes(t_data *data, char *tmp);
//char	*rm_bracket(t_data *data, char *tmp);

#endif