/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:58:48 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/21 13:13:48 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	setup_dup(int fd_in, int fd_out, t_exc *tool);

bool	exec_multi_redirections(t_token *segment, t_exc *tool)
{
	int		fd_in;
	int		fd_out;
	bool	state;

	fd_in = 0;
	fd_out = 0;
	if (!prepare_dup(segment, &fd_in, &fd_out))
		return (false);
	state = setup_dup(fd_in, fd_out, tool);
	return (state);
}

static bool	setup_dup(int fd_in, int fd_out, t_exc *tool)
{
	if (fd_in > 0)
	{
		if (dup2(fd_in, 0) == -1)
			return (false);
	}
	else
		dup2(tool->read, STDIN_FILENO);
	if (fd_out > 0)
	{
		if (dup2(fd_out, 1) == -1)
			return (false);
	}
	else
		dup2(tool->write, STDOUT_FILENO);
	return (true);
}

bool	exec_redirections(t_token *segment)
{
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 0;
	if (!prepare_dup(segment, &fd_in, &fd_out))
		return (false);
	if (fd_in > 0)
		if (dup2(fd_in, 0) == -1)
			return (false);
	if (fd_out > 0)
		if (dup2(fd_out, 1) == -1)
			return (false);
	return (true);
}
