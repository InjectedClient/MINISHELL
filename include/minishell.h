/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:00 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 16:52:05 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*SIGNAL*/
# define IGNORE_SIG_ACTION SIG_IGN
# define CTRL_C_SIGINT SIGINT
# define CTRL_BACKSLSH SIGQUIT
# define SHIFT_OUT 14
# define STDOUT_FILENO 1

/* ━━━━━━━━━━━━━━━━━━━━━ BIBLIO ━━━━━━━━━━━━━━━━━━━━━━━━*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h> 

extern unsigned int	g_global;

typedef enum s_token{
	CMD,
	ARG,
	REDIRECT_OUT,
	APPEND_OUT,
	REDIRECT_IN,
	HERE_DOC,
	REDIRECT_INOUT,
	REDIRECT_OUTIN,
	FD,
	DELIMITER,
	PIPE,
}	t_token;

typedef struct s_quote
{
	int				singl_quot_status;
	int				doubl_quot_status;
	int				singl_quot_start_status;
}	t_quote;

typedef struct s_lexer
{
	int				segment_position;
	char			*cmd_segment;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_free_memory
{
	void					*add;
	struct s_free_memory	*next;
}	t_free_memory;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal_sign;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	t_lexer			*lexer_list;
	t_lexer			*tokens;
	t_free_memory	*free_memory;
	int				w_count;
	int				is_sing_quot;
	int				is_doub_quot;
	char			*input_cmd;
	int				command_count;
	int				sig1;
	int				sig2;
	char			**args;
}	t_data;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ PARSER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	init_data(t_data *data, int argc, char **argv);
int		check_quotes(char *str, t_data *data);
int		check_redirections(char *str);
int		check_cmd_start(char *str);
int		check_redirection_arg(t_data *data);
int		check_invalid_pipes(t_data *data);
int		nb_redir(char *str);
int		check_token_error(t_data *data);
int		check_invalid_tokens(t_data *data);
int		check_invalid_tokens2(t_data *data);
int		check_slash(char *str, char c);
int		check_directory(char *str);
int		check_pipe_bracket(char *str);
int		ft_check_parser(t_data *data);
int		is_a_directory(t_data *data);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ SIGNAL ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	new_line(int sig);
void	reset_prompt(int sig);
void	signals_wait_cmd(void);
void	signals_run_cmd(void);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ UTILS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

int		ft_strncmp(const char *first, const char *second, size_t length);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	free_array(char **array);
int		ft_white_space(char c);
char	**ft_split(char const *s, char c);
void	exit_all(t_data *data);
void	ft_free_all(t_data *data);
void	free_tab(char **tab);
int		ft_write_fd(char *str, int fd);
char	*ft_strdup(const char *source);
int		ft_atoi(const char *str);
int		get_num_len(int n);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
void	add_to_free_memory(t_data *data, void *add);
void	*malloc_track(t_data *data, size_t size);
char	*ft_strndup(const char *source, size_t size);
char	*ft_strchr(const char *str, int searchedChar);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);

void	free_2(char *var1, char *var2);
void	free_3(char *var1, char *var2, char *var3);
void	free_4(char *var1, char *var2, char *var3, char *var4);
void	free_env_node(t_env *node);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LEXER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	lexer_launch(t_data *data);
void	looping(char *tmp, t_data *data, t_env *env_list, char **envp);
int		count_words_in_input(char *str);
void	process_input_string(\
		t_data *data, t_lexer *tmp, t_lexer *current, int i);
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

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int		exec_cmd(char **cmd, char *envp[], t_env *env_list);
int		exec(char *cmd[], t_env *env_list, char **envp, int fork);
int		execute_token(t_data *data, t_env *env_list, char **envp);

//Args
int		count_args(t_lexer *arg);
char	**split_args(t_lexer *cmd);

//Path
char	*get_cmd_path(char *cmd, t_env *env_list);
char	*ft_getenv(char *path, t_env *env_list);
char	*ft_getenv_dup(char *path, t_env *env_list);

//Builtins
int		is_builtin(char *cmd);
int		exec_builtins(char **args, t_env *env_list);

int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env **env_list);
int		builtin_pwd(void);
int		builtin_export(char **args, t_env **env_list);
void	update_or_add_env(t_env **env_list, char *arg);
int		builtin_unset(char **args, t_env **env_list);
int		builtin_env(t_env *env_list);
int		builtin_exit(char **args);

//Heredoc
int		handle_here_doc(const char *delimiter);
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXPAND ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	expand_command(t_data *data, t_env *env_list);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ERRORS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Error
int		error(void);
int		malloc_error(void);
int		cmd_not_exec(void);
int		cmd_not_found(void);
int		fork_error(void);
t_env	*init_env_list(char **envp);

#	endif
