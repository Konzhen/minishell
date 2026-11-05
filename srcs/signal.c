/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:58:40 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 13:46:42 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signal)
{
	(void)signal;
	rl_done = 1;
	g_exit = -130;
}

void	ctrl_d(int signal)
{
	(void)signal;
	printf("\n");
	exit (g_exit);
}

int	for_rl_event_hook(void)
{
	return (0);
}

void	set_signal(void)
{
	rl_event_hook = for_rl_event_hook;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
