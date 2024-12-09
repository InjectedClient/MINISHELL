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

/* ━━━━━━━━━━━━━━━━━━━━━ STRUCTURES ━━━━━━━━━━━━━━━━━━━━━━━━*/

/*
	definit les differents types de tokens que le lexer peut ID.
*/
typedef enum s_token{
	CMD,			// Commande : représente une commande à exécuter
	ARG,			// Argument : représente un argument de commande
	REDIRECT_OUT,	// Redirection de sortie : '>' redirige la sortie standard vers un fichier
	APPEND_OUT,		// Redirection d'ajout : '>>' ajoute la sortie standard à la fin d'un fichier
	REDIRECT_IN,	// Redirection d'entrée : '<' redirige l'entrée standard depuis un fichier
	HERE_DOC,		// Here document : '<<' permet d'utiliser un bloc de texte comme entrée standard
	REDIRECT_INOUT,	// Redirection entrée et sortie : '<>' redirige à la fois l'entrée et la sortie
	REDIRECT_OUTIN,	// Redirection sortie et entrée : '><' redirige à la fois la sortie et l'entrée
	FD,				// Descripteur de fichier : représente un descripteur de fichier
	DELIMITER,		// Délimiteur : représente un délimiteur utilisé dans les here documents
	PIPE,			// Pipe : '|' redirige la sortie d'une commande vers l'entrée d'une autre
} t_token;

typedef struct s_quote
{
	int				singl_quot_status;
	int				doubl_quot_status;
	int				singl_quot_start_status;
	int				var_env_match_confirmed;
}	t_quote;
/*
	contiens la liste chainee de token + le nombre
*/
typedef struct s_lexer
{
	int				segment_position;
	char			*cmd_segment;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

/*
	contiens les donnees globales / composition d'autre struct
	(variable d'env, historique des commmandes etc... )
*/
typedef struct s_data {
	t_lexer *lexer_list;
	t_lexer *tokens;
	int		w_count;
	int		is_sing_quot;
	int		is_doub_quot;
	char	*input_cmd;
	int		command_count;
	char	**args;
}	t_data;


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

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LEXER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	lexer_launch(t_data *data);
void	looping(char *tmp, t_data *data, char *envp[]);
int		count_words_in_input(char *str);
void	test_cmd(t_data*data);
void	process_input_string(t_data *data, t_lexer *tmp, t_lexer *current, int i);
int		check_prev(t_lexer *token);
void	cmd_or_arg(t_lexer *tmp, t_lexer *first);
int		get_word_in_list(char *str, int i, t_data *data, t_lexer *tmp);
void	add_lexer_to_end(t_data *data, char *str);
t_lexer	*create_new_lexer(char *str);
void	get_token_in_node(t_lexer **lexer_list, t_lexer *tmp);
void	print_lexer_content(t_data *data);
t_token	which_redir(t_lexer *tmp);
int		check_redir_error(t_lexer *tmp);
int		check_redirect(const char *cmd, char c);
void	get_data_in_node(t_lexer **lexer_list);
char	*add_space(const char *command);
size_t	calculate_new_length(const char *command);
int		is_operator(char c);
int		is_double_operator(const char *command, size_t pos);
void	fill_command_with_spaces(const char *command, char *new_command, \
		t_quote *state, size_t i);
void	update_quoting_state(char c, t_quote *state);
int		is_single_quote_open(t_quote *state);
int		is_single_quote_closed(t_quote *state);
int		is_doubl_quote_open(t_quote *state);
int		is_doubl_quote_closed(t_quote *state);
int		is_only_single_quote_on(t_quote *state);
void	reset_quoting_state(t_quote *state);
void	process_lexer_input(char *str, int *i, int *j, t_quote *state);
char **convert_list_to_array(t_lexer *head);
int 	count_lexer_list(t_lexer *head);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main
char    *get_path_from_env(char *name, char *envp[]);
char    *get_cmd_path(char *cmd, char *envp[]);
void    exec(char *cmd[], char *envp[]);

char	**ft_split(char const *s, char c);

// Utils 1
int	ft_strncmp(const char *first, const char *second, size_t length);
int	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

// Utils 2
void free_array(char **array);

// Error
void exit_with_error(const char *message, int exit_code);
void free_tab_and_exit(char **ptr);
void *malloc_check(void *ptr);

void get_input(int argc, char **argv, char *envp[]);
#	endif
