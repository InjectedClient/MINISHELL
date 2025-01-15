/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlambert <nlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:38:44 by nlambert          #+#    #+#             */
/*   Updated: 2025/01/15 11:15:50 by nlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_here_doc(const char *delimiter)
{
	static int counter = 0; // Compteur unique
	char temp_file[256] = "/tmp/minishell_heredoc_";
	char *counter_str;
	char *line;
	int temp_fd;
	int i;

	// Convertir le compteur en chaîne (itoa)
	counter_str = malloc(12); // Assez pour un entier
	if (!counter_str)
		return (-1);
	int temp = counter;
	i = 0;
	while (temp > 0)
	{
		counter_str[i++] = '0' + (temp % 10);
		temp /= 10;
	}
	counter_str[i] = '\0';

	// Ajouter le compteur au nom du fichier
	strcat(temp_file, counter_str);
	free(counter_str);
	counter++; // Incrémenter le compteur pour le prochain fichier

	// Créer le fichier temporaire
	temp_fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}

	// Lire l'entrée jusqu'au délimiteur
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0) // EOF ou délimiteur atteint
		{
			free(line);
			break;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1); // Ajouter un saut de ligne
		free(line);
	}

	close(temp_fd);       // Fermer en écriture
	temp_fd = open(temp_file, O_RDONLY); // Réouvrir en lecture
	if (temp_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	unlink(temp_file);    // Supprimer le fichier temporaire
	return temp_fd;       // Retourner le descripteur du fichier
}
