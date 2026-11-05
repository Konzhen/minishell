/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:33:25 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:50:40 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_pipeline_running(t_token **segment, t_env **p_envlst);
static bool	manage_builtin(t_token **segment, t_env **p_envlst);
static void	manage_execution(t_token **segment, t_env **p_envlst);
static void	npr_next(int tmp_exit);

bool	running_managment(t_token **tab, t_env **p_envlst)
{
	int		len;
	bool	state;

	len = tablen((void **)tab);
	state = true;
	if (len == 1)
		state = no_pipeline_running(tab, p_envlst);
	else
		state = pipeline_running(tab, p_envlst);
	clean_fd();
	return (state);
}

static bool	no_pipeline_running(t_token **segment, t_env **p_envlst)
{
	int		pid;
	int		tmp_exit;
	int		i;

	tmp_exit = 0;
	i = 0;
	while (segment[0][i].type != END)
	{
		if (segment[0][i].type == BUILT_IN)
			return (manage_builtin(segment, p_envlst));
		else if (segment[0][i].type == COMMAND)
		{
			pid = fork();
			if (pid == 0)
				manage_execution(segment, p_envlst);
			else
				waitpid(pid, &tmp_exit, 0);
			npr_next(tmp_exit);
			return (true);
		}
		i++;
	}
	return (true);
}

static void	npr_next(int tmp_exit)
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

static bool	manage_builtin(t_token **segment, t_env **p_envlst)
{
	int		cpy_in;
	int		cpy_out;
	bool	state;

	cpy_in = dup(STDIN_FILENO);
	cpy_out = dup(STDOUT_FILENO);
	state = true;
	if (exec_redirections(segment[0]))
		state = exec_builtin(segment, 0, p_envlst, -1);
	if (cpy_in != -1)
		dup2(cpy_in, STDIN_FILENO);
	if (cpy_out != -1)
		dup2(cpy_out, STDOUT_FILENO);
	multi_closing(cpy_out, cpy_in, -1, -1);
	return (state);
}

static void	manage_execution(t_token **segment, t_env **p_envlst)
{
	char	**env_toexec;
	int		i;

	i = 0;
	env_toexec = lst_to_array(p_envlst);
	if (exec_redirections(segment[0]))
	{
		if (env_toexec)
		{
			get_cmds(segment[0], env_toexec);
			while (segment[0][i].type != END)
			{
				if (segment[0][i].type == COMMAND)
				{
					exec_cmd(&segment[0][i], env_toexec);
					break ;
				}
				i++;
			}
		}
		lst_destroy(*p_envlst);
		error_gestion(segment, env_toexec, 0, i);
	}
	error_if_redir_fail(segment, p_envlst, env_toexec);
}
