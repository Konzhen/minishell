/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:04:14 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:49:14 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_dup(t_token *segment, int i, int *fd_in, int *fd_out);

static bool	set_exec_fd(t_token *token, int *fd)
{
	*fd = token->file->fd;
	if (*fd == -1)
		return (false);
	return (true);
}

bool	prepare_dup(t_token *segment, int *fd_in, int *fd_out)
{
	int	i;

	i = 0;
	while (segment[i].type != END)
	{
		if (segment[i].type == TFILE)
		{
			if (!handle_dup(segment, i, fd_in, fd_out))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	handle_dup(t_token *segment, int i, int *fd_in, int *fd_out)
{
	if (segment[i].file->redir_type == OUT
		|| segment[i].file->redir_type == APPEND_OUT)
	{
		if (!set_exec_fd(&segment[i], fd_out))
			return (false);
	}
	else if (segment[i].file->redir_type == IN)
	{
		if (!set_exec_fd(&segment[i], fd_in))
			return (false);
	}
	else
	{
		if (!set_exec_fd(&segment[i], fd_in))
			return (false);
	}
	return (true);
}
