/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_for_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 08:55:46 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:52:26 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redir_in(t_file *file)
{
	int	fd;

	if (!*file->name)
		fd = -1;
	else
		fd = open(file->name, O_RDONLY);
	file->fd = fd;
	if (fd == -1)
	{
		err_file_msg(file->name, false);
		return (false);
	}
	return (true);
}

static bool	redir_out(t_file *file)
{
	int		fd;
	bool	is_valid_name;

	is_valid_name = true;
	if (!*file->name)
	{
		fd = -1;
		is_valid_name = false;
	}
	else
	{
		fd = 0;
		if (file->redir_type == OUT)
			fd = open(file->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (file->redir_type == APPEND_OUT)
			fd = open(file->name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	file->fd = fd;
	if (fd == -1)
	{
		err_file_msg(file->name, is_valid_name);
		return (false);
	}
	return (true);
}

static bool	get_fd(t_token *token, bool heredoc)
{
	if (!heredoc)
	{
		if (token->file->redir_type == OUT
			|| token->file->redir_type == APPEND_OUT)
		{
			if (!redir_out(token->file))
				return (false);
		}
		else if (token->file->redir_type == IN)
		{
			if (!redir_in(token->file))
				return (false);
		}
	}
	else
	{
		if (token->file->redir_type == HEREDOC)
		{
			if (!redir_heredoc(token->file))
				return (false);
		}
	}
	return (true);
}

void	open_files(t_token **tab, bool heredoc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j].type != END)
		{
			if (tab[i][j].type == TFILE)
			{
				if (!get_fd(&tab[i][j], heredoc))
					break ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
