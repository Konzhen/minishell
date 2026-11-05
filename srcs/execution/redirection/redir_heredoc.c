/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:03:30 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:49:29 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_printing(char *str);

bool	redir_heredoc(t_file *file)
{
	char	*input;
	char	*tmp;

	if (g_exit != -130)
	{
		if (pipe(file->hdfd) == -1)
			return (false);
		file->fd = file->hdfd[0];
		input = readline("> ");
		while ((ft_strcmp(file->name, input) != 0))
		{
			if (input == NULL || g_exit == -130)
				break ;
			tmp = ft_strjoin(input, "\n");
			ft_putstr_fd(tmp, file->hdfd[1]);
			free(tmp);
			free(input);
			input = readline("> ");
		}
		if (input == NULL)
			error_printing(file->name);
		free(input);
		close(file->hdfd[1]);
	}
	return (true);
}

static void	error_printing(char *str)
{
	ft_putstr_fd("zook_shell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
}
