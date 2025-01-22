/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:54 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 13:13:28 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	starts_with_tilde(const char *cmd_segment)
{
	if (!cmd_segment)
		return 0;
	return (cmd_segment[0] == '~');
}

int	starts_with_dollar(const char *cmd_segment)
{
	if (!cmd_segment)
		return 0;
	return (cmd_segment[0] == '$');
}


void *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;
    size_t i;

    if (!dst && !src) // Gérer les cas où les deux pointeurs sont NULL
        return NULL;

    d = (unsigned char *)dst;
    s = (const unsigned char *)src;

    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }

    return dst;
}

size_t ft_strlen_until(const char *str, const char *stop_chars)
{
    size_t i = 0;

    if (!str || !stop_chars)
        return 0;

    while (str[i])
    {
        size_t j = 0;
        while (stop_chars[j])
        {
            if (str[i] == stop_chars[j]) // Arrête si un caractère correspond
                return i;
            j++;
        }
        i++;
    }

    return i; // Retourne la longueur totale si aucun caractère ne correspond
}

char *remove_quotes(const char *input)
{
    char *result = malloc(ft_strlen(input) + 1);
    int i = 0, j = 0;
    t_quote quote_status = {0, 0, 0};

    if (!result)
        return NULL;

    while (input[i])
    {
        if (input[i] == '\'' && !quote_status.doubl_quot_status)
            quote_status.singl_quot_status = !quote_status.singl_quot_status;
        else if (input[i] == '\"' && !quote_status.singl_quot_status)
            quote_status.doubl_quot_status = !quote_status.doubl_quot_status;
        else
            result[j++] = input[i];
        i++;
    }
    result[j] = '\0';
    return result;
}


char *expand_variable(const char *input, t_env *env_list, int in_single_quote)
{
    if (in_single_quote)
        return ft_strdup(input); // Retourne tel quel dans les quotes simples

    const char *start = input + 1; // Ignore le $
    size_t len = 0;

    if (*start == 34 || *start == '\0') // Cas où c'est uniquement "$"
        return ft_strdup("$");

    if (*start == '?') // Cas de "$?"
    {
        char *ret = ft_itoa(g_global);
        char *remaining = ft_strdup(start + 1); // Copie le reste après "?"
        char *result = ft_strjoin(ret, remaining); // Concatène la valeur et le reste
        free(ret);
        free(remaining);
        return result;
    }

    while (start[len] && (ft_isalnum(start[len]) || start[len] == '_'))
        len++;

    char *var_name = ft_substr(start, 0, len);
    char *value = ft_getenv(var_name, env_list); // Cherche la variable
    free(var_name);

    if (value)
    {
        char *remaining = ft_strdup(start + len); // Copie le reste après la variable
        char *result = ft_strjoin(value, remaining); // Concatène la valeur et le reste
        free(remaining);
        return result;
    }
    return ft_strdup(""); // Retourne une chaîne vide si la variable n'existe pas
}




char	*expand_tilde(const char *input, t_env *env_list)
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
    t_quote quote_status = {0, 0, 0}; // Structure pour suivre l'état des quotes
    char *expanded = malloc(1024); // Stocker le segment expansé
    int i = 0, j = 0;

    if (!expanded)
        return NULL;

    while (token->cmd_segment[i])
    {
        if (token->cmd_segment[i] == '\'' && !quote_status.doubl_quot_status)
        {
            quote_status.singl_quot_status = !quote_status.singl_quot_status;
            i++;
        }
        else if (token->cmd_segment[i] == '\"' && !quote_status.singl_quot_status)
        {
            quote_status.doubl_quot_status = !quote_status.doubl_quot_status;
            i++;
        }
        else if (token->cmd_segment[i] == '$')
        {
            // Expansion des variables avec respect des quotes
            char *var_expanded = expand_variable(&token->cmd_segment[i], env_list, quote_status.singl_quot_status);
            if (var_expanded)
            {
                size_t len = ft_strlen(var_expanded);
                ft_memcpy(&expanded[j], var_expanded, len);
                j += len;
                i += ft_strlen_until(&token->cmd_segment[i], " \t\"\'"); // Avancer
                free(var_expanded);
            }
        }
        else
        {
            expanded[j++] = token->cmd_segment[i++];
        }
    }

    expanded[j] = '\0';
    return expanded;
}


void expand_command(t_data *data, t_env *env_list)
{
    t_lexer *current = data->lexer_list;

    while (current)
    {
        char *expanded = expand_token(current, env_list); // Expansion du token
        if (!expanded)
        {
            perror("minishell: expansion failed");
            exit(1); // Gère proprement l'erreur
        }
        char *cleaned = remove_quotes(expanded); // Supprime les quotes
        free(expanded);
        free(current->cmd_segment); // Libère l'ancien segment
        current->cmd_segment = cleaned; // Remplace par le segment expansé et nettoyé
        current = current->next;
    }
}

