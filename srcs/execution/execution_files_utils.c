/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_files_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:38 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 14:22:53 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disp_next_cmb(t_token **segment, int index_up, int index_deep, \
						t_env **p_envlst);
static bool	to_do_to_exec(t_token **segment, t_env **p_envlst, int tool[2], \
						pid_t pid);

bool	dispatching(t_token **segment, int index, t_env **p_envlst, pid_t pid)
{
	int		i;
	bool	state;

	i = 0;
	state = true;
	while (segment[index][i].type != END)
	{
		if (segment[index][i].type == BUILT_IN)
		{
			state = exec_builtin(segment, index, p_envlst, pid);
			if (state)
				tok_free(&segment);
			lst_destroy(*p_envlst);
			return (state);
		}
		else if (segment[index][i].type == COMMAND)
		{
			disp_next_cmb(segment, index, i, p_envlst);
			return (state);
		}
		i++;
	}
	tok_free(&segment);
	lst_destroy(*p_envlst);
	return (state);
}

static void	disp_next_cmb(t_token **segment, int index_up, int index_deep, \
						t_env **p_envlst)
{
	char	**env_toexec;

	env_toexec = lst_to_array(p_envlst);
	lst_destroy(*p_envlst);
	if (env_toexec)
	{
		get_cmds(segment[index_up], env_toexec);
		exec_cmd(&segment[index_up][index_deep], env_toexec);
		error_gestion(segment, env_toexec, index_up, index_deep);
		tok_free(&segment);
	}
	else
		tok_free(&segment);
}

bool	exec_builtin(t_token **s, int index_up, t_env **p_envlst, \
				pid_t pid)
{
	int		tool[2];

	tool[0] = index_up;
	tool[1] = 0;
	while (s[index_up][tool[1]].type != END)
	{
		if (s[index_up][tool[1]].type == BUILT_IN)
		{
			if (!ft_strncmp((char *)s[index_up][tool[1]].word[0], "pwd", \
					ft_strlen((char *)s[index_up][tool[1]].word[0])))
				ft_pwd();
			else if ((!ft_strncmp((char *)s[index_up][tool[1]].word[0], \
			"cd", 2)) ||
			(!ft_strncmp((char *)s[index_up][tool[1]].word[0], "export", 6)) || \
			(!ft_strncmp((char *)s[index_up][tool[1]].word[0], "echo", 4)) || \
			(!ft_strncmp((char *)s[index_up][tool[1]].word[0], "exit", 4)) || \
			(!ft_strncmp((char *)s[index_up][tool[1]].word[0], "unset", 5)) || \
			(!ft_strncmp((char *)s[index_up][tool[1]].word[0], "env", 3)))
				return (to_do_to_exec(s, p_envlst, tool, pid));
		}
		tool[1]++;
	}
	return (true);
}

static bool	to_do_to_exec(t_token **segment, t_env **p_envlst, int tool[2], \
						pid_t pid)
{
	char	**towork;
	char	*str;

	if (segment[tool[0]][tool[1] + 1].word == NULL)
	{
		towork = strdup_tab(segment[tool[0]][tool[1]].word);
		str = ft_strdup(towork[0]);
	}
	else
	{
		towork = turn_tok_into_array(segment, tool[0]);
		str = ft_strdup(segment[tool[0]][tool[1]].word[0]);
	}
	if (!ft_strncmp((char *)segment[tool[0]][tool[1]].word[0], "exit", 4))
	{
		clean_fd();
		tok_free(&segment);
	}
	return (e_builtin(towork, str, p_envlst, pid));
}

void	exec_cmd(t_token *token, char **env)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (token->cmd->path_cmd)
		execve(token->cmd->path_cmd, token->cmd->tab_cmd, env);
	return ;
}
