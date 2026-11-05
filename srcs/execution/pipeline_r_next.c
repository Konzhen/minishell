/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_r_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:54:31 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:49:50 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_exit_value(int tmp_exit);

void	pipeline_r_next(t_exc *tool)
{
	int		tmp_exit;

	tmp_exit = 0;
	tool->index = 0;
	while (tool->index < tool->len)
	{
		if (tool->index < tool->len - 2)
			waitpid(tool->pid_array[tool->index], NULL, 0);
		else
			waitpid(tool->pid_array[tool->index], &tmp_exit, 0);
		tool->index++;
	}
	build_exit_value(tmp_exit);
	free(tool->pid_array);
	tool->pid_array = NULL;
}

static void	build_exit_value(int tmp_exit)
{
	if (WEXITSTATUS(tmp_exit))
		g_exit = WEXITSTATUS(tmp_exit);
	else if (WCOREDUMP(tmp_exit))
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_exit = WTERMSIG(tmp_exit) + 128;
	}
	else if (WIFSIGNALED(tmp_exit))
	{
		ft_putstr_fd("\n", 2);
		g_exit = WTERMSIG(tmp_exit) + 128;
	}
	else
		g_exit = 0;
}

void	destroy_error(t_token **array, t_env **p_envlst)
{
	lst_destroy(*p_envlst);
	tok_free(&array);
}
