/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_running.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:54:18 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:52:35 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_tool_process(t_token **array, t_exc *tool);
static bool	handle_child_process(t_token **array, t_exc *tool);
static void	handle_parent_process(t_exc *tool);
static void	hpp_next(t_exc *tool);

bool	pipeline_running(t_token **array, t_env **p_envlst)
{
	t_exc	tool;
	bool	state;

	state = true;
	if (setup_tool_process(array, &tool) == -1)
		return (state);
	while (tool.index < tool.len)
	{
		handle_parent_process(&tool);
		signal(SIGINT, SIG_IGN);
		tool.pid_array[tool.index] = fork();
		if (tool.pid_array[tool.index] == 0)
		{
			if (handle_child_process(array, &tool))
				state = dispatching(array, tool.index, p_envlst, 0);
			else
				destroy_error(array, p_envlst);
			exit (1);
		}
		hpp_next(&tool);
		tool.index++;
	}
	pipeline_r_next(&tool);
	return (state);
}

static int	setup_tool_process(t_token **array, t_exc *tool)
{
	tool->index = 0;
	tool->len = tablen((void **)array);
	tool->pid_array = ft_calloc(sizeof(int), tool->len);
	if (!tool->pid_array)
		return (-1);
	tool->read = 0;
	tool->write = 1;
	return (0);
}

static void	handle_parent_process(t_exc *tool)
{
	if (tool->index < tool->len - 1)
		pipe(tool->pipefd);
	else
	{
		tool->pipefd[0] = 0;
		tool->pipefd[1] = 1;
	}
	if (tool->write != 1)
		close (tool->write);
	tool->write = tool->pipefd[1];
}

static bool	handle_child_process(t_token **array, t_exc *tool)
{
	bool	state;

	state = exec_multi_redirections(array[tool->index], tool);
	if (tool->write != 1)
		close(tool->write);
	if (tool->read != 0)
		close(tool->read);
	if (tool->pipefd[1] != 1)
		close(tool->pipefd[1]);
	if (tool->pipefd[0] != 0)
		close(tool->pipefd[0]);
	free(tool->pid_array);
	clean_fd();
	return (state);
}

static void	hpp_next(t_exc *tool)
{
	if (tool->read != 0)
		close(tool->read);
	tool->read = tool->pipefd[0];
}
