#ifndef MINISHELL_H
# define MINISHELL_H

/*SIGNAL*/
# define IGNORE_SIG_ACTION SIG_IGN
# define CTRL_C_SIGINT SIGINT
# define CTRL_BACKSLSH SIGQUIT
# define SHIFT_OUT 14
#define	STDOUT_FILENO 1

/* ━━━━━━━━━━━━━━━━━━━━━ BIBLIO ━━━━━━━━━━━━━━━━━━━━━━━━*/

// Standard librairies
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>  // wait, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG

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

typedef struct s_free_memory
{
	void					*add;
	struct s_free_memory	*next;
}	t_free_memory;

//Builtins
typedef struct {
    char *name;                       // Nom du builtin
    int (*function)(char **args);     // Pointeur vers la fonction du builtin
} builtin_t;

// Liste pour variables denvironnement
typedef struct s_env
{
    char *name;
    char *value;
	int		equal_sign;
    struct s_env *next;
} t_env;

/*
	contiens les donnees globales / composition d'autre struct
	(variable d'env, historique des commmandes etc... )
*/
typedef struct s_data {
	t_lexer *lexer_list;
	t_lexer *tokens;
	t_free_memory	*free_memory;
	int		w_count;
	int		is_sing_quot;
	int		is_doub_quot;
	char	*input_cmd;
	int		command_count;
	int 	sig1; //(is this an exec in heredoc)
	int		sig2; // (heredoc ctrl_c uninterrupted)
	char	**args;
}	t_data;

extern unsigned int g_global;

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

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ SIGNAL ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	handle_ctrl_c(int sig);
void	handle_signal(void);
void	handle_ctrl_backslash(int sig);
void	handle_sig(t_data *data);
void	ctrl_c_handler_here_doc(int sig);
void	ctrl_c_handler(int sig);

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
int 	ft_strcmp(const char *s1, const char *s2);

void    free_2(char *var1, char *var2);
void    free_3(char *var1, char *var2, char *var3);
void    free_4(char *var1, char *var2, char *var3, char *var4);
void	free_env_node(t_env *node);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LEXER ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

void	lexer_launch(t_data *data);
void 	looping(char *tmp, t_data *data, t_env *env_list, char **envp);
int		count_words_in_input(char *str);
void	process_input_string(t_data *data, t_lexer *tmp, t_lexer *current, int i);
int		check_prev(t_lexer *token);
void	cmd_or_arg(t_lexer *tmp, t_lexer *first);
int		get_word_in_list(char *str, int i, t_data *data, t_lexer *tmp);
void	add_lexer_to_end(t_data *data, char *str);
t_lexer *create_new_lexer(char *str);
void	get_token_in_node(t_lexer **lexer_list, t_lexer *tmp);
void	print_lexer_content(t_data *data);
t_token	which_redir(t_lexer *tmp);
int		check_redir_error(t_lexer *tmp);
int		check_redirect(const char *cmd, char c);
void	get_data_in_node(t_lexer **lexer_list);
char *add_space(const char *command);
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
char	**convert_list_to_array(t_lexer *head);
int 	count_lexer_list(t_lexer *head);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXECUTOR ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int    exec_cmd(char **cmd, char *envp[]);
int    exec(char *cmd[], t_env *env_list, char **envp);
int execute_token(t_data data, t_env *env_list, char **envp);

//Args
int     count_args(t_lexer *arg);
char    **split_args(t_lexer *cmd);

//Path
char    *get_cmd_path(char *cmd, char *path_var);

//Builtins
int     is_builtin(char *cmd);
int 	exec_builtins(char **args, t_env *env_list);

int     builtin_echo(char **args);
int     builtin_cd(char **args);
int     builtin_pwd();
int 	builtin_export(char **args, t_env **env_list);
int		builtin_unset(char **args, t_env **env_list);
int		builtin_env(t_env *env_list);
int     builtin_exit(char **args);


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ EXPAND ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

char	*expander(char *str);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ ERRORS ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Error
int error();
int malloc_error();
int cmd_not_exec();
int cmd_not_found();
int fork_error();


t_env *init_env_list(char **envp);

# endif
