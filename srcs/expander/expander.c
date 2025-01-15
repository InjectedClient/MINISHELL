/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:54 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 11:13:26 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// int is_single_quote(const char *cmd_segment)
// {
//     size_t len;

//     if (!cmd_segment)
//         return 0;

//     len = ft_strlen(cmd_segment);
//     return (len >= 2 && cmd_segment[0] == '\'' && cmd_segment[len - 1] == '\'');
// }

// int is_double_quote(const char *cmd_segment)
// {
//     size_t len;

//     if (!cmd_segment)
//         return 0;

//     len = ft_strlen(cmd_segment);
//     return (len >= 2 && cmd_segment[0] == '"' && cmd_segment[len - 1] == '"');
// }

int starts_with_tilde(const char *cmd_segment)
{
	if (!cmd_segment)
		return 0;
	return (cmd_segment[0] == '~');
}

int starts_with_dollar(const char *cmd_segment)
{
	if (!cmd_segment)
		return 0;
	return (cmd_segment[0] == '$');
}


// char *handle_single_quote(const char *input)
// {
//     char *result = ft_strtrim(input, "'"); // Retire les guillemets simples.
//     return result ? result : strdup("");  // Si rien, retourne une chaîne vide.
// }

// char *handle_double_quote(const char *input, t_env *env_list)
// {
//     char *trimmed = ft_strtrim(input, "\""); // Retire les guillemets doubles.
//     char *expanded = expand_variable(trimmed, env_list); // Expansion des variables.
//     free(trimmed);
//     return expanded;
// }

char *expand_variable(const char *input, t_env *env_list)
{
	const char *start;
	size_t	len;
	char	*var_name;
	char	*value;

	if (input[0] != '$')
		return (ft_strdup(input));

	start = input + 1;
	if (*start == '?')
	{
		char *ret = ft_itoa(g_global);
		return (ret);
	}
	len = 0;
	while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
		len++;

	var_name = ft_substr(start, 0, len); // Extrait le nom de la variable.
	value = ft_getenv(var_name, env_list); // Récupère sa valeur.
	free(var_name);

	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
	//return value ? strdup(value) : strdup(""); // Si non définie, retourne une chaîne vide.
}


char *expand_tilde(const char *input, t_env *env_list)
{
	char	*home;
	if (input[0] != '~')
		return ft_strdup(input);

	home = ft_getenv("HOME", env_list); // Récupère $HOME.
	if (!home)
		return ft_strdup(input); // Si pas de HOME, retourne le chemin inchangé.
	return ft_strjoin(home, input + 1); // Concatène $HOME avec le reste du chemin.
}


char *expand_token(t_lexer *token, t_env *env_list)
{
	// if (is_single_quote(token->cmd_segment))
	//     return handle_single_quote(token->cmd_segment); // Pas d'expansion pour les guillemets simples.
	// if (is_double_quote(token->cmd_segment))
	//     return handle_double_quote(token->cmd_segment, env_list); // Expansion des variables dans les doubles quotes.
	if (starts_with_tilde(token->cmd_segment))
		return expand_tilde(token->cmd_segment, env_list); // Expansion de ~ en $HOME.
	if (starts_with_dollar(token->cmd_segment))
		return expand_variable(token->cmd_segment, env_list); // Expansion des variables d'environnement.

	return strdup(token->cmd_segment); // Si rien à faire, retourne tel quel.
}

void expand_command(t_data *data, t_env *env_list)
{
	t_lexer *current = data->lexer_list;

	while (current)
	{
		char *expanded = expand_token(current, env_list); // Expansion du token.
		if (!expanded)
		{
			perror("minishell: expansion failed");
			exit(1); // Gère proprement l'erreur.
		}
		free(current->cmd_segment); // Libère l'ancien segment.
		current->cmd_segment = expanded; // Remplace par le segment expansé.
		current = current->next;
	}
}
