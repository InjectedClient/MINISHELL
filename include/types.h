#ifndef TYPES_H
# define TYPES_H

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

#endif