/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efu_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:54:20 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:48:29 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dirctory_error(t_token **token, char **env, int index_up, \
				int index_deep);
static void	file_error(t_token **token, char **env, int index_up, \
				int index_deep);

void	error_gestion(t_token **token, char **env, int index_up, \
				int index_deep)
{
	if (!token || !*token)
		return ;
	if (token[index_up][index_deep].cmd && \
		token[index_up][index_deep].cmd->path_cmd && \
		is_directory(token[index_up][index_deep].cmd->path_cmd))
		dirctory_error(token, env, index_up, index_deep);
	else if (token[index_up][index_deep].cmd && \
		token[index_up][index_deep].cmd->path_cmd && \
		!is_executable_file(token[index_up][index_deep].cmd->path_cmd))
		file_error(token, env, index_up, index_deep);
	if (!token[index_up][index_deep].cmd)
	{
		if (env)
			free_tab((void **)env, 0);
		tok_free(&token);
		return ;
	}
	ft_putstr_fd(token[index_up][index_deep].word[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (env)
		free_tab((void **)env, 0);
	tok_free(&token);
	exit (127);
}

void	error_if_redir_fail(t_token **segment, t_env **p_envlst, \
						char **env_toexec)
{
	lst_destroy(*p_envlst);
	free_tab((void **)env_toexec, 0);
	tok_free(&segment);
	exit (1);
}

static void	dirctory_error(t_token **token, char **env, int index_up, \
				int index_deep)
{
	ft_putstr_fd(token[index_up][index_deep].cmd->path_cmd, 2);
	ft_putstr_fd(": Is a Directory\n", 2);
	if (env)
		free_tab((void **)env, 0);
	tok_free(&token);
	exit (126);
}

static void	file_error(t_token **token, char **env, int index_up, \
				int index_deep)
{
	ft_putstr_fd(token[index_up][index_deep].cmd->path_cmd, 2);
	ft_putstr_fd(": Permission dinied\n", 2);
	if (env)
		free_tab((void **)env, 0);
	tok_free(&token);
	exit (126);
}
