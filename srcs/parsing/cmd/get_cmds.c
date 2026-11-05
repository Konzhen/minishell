/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:35:08 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:35:10 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	absolute_path(t_token *token);

static char	**get_tab_cmd(t_token *segment, int size)
{
	char	**tab_cmd;
	int		i;
	int		j;

	size = calculate_args(segment);
	tab_cmd = ft_calloc(size + 1, sizeof(char *));
	if (!tab_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size)
	{
		if ((*segment).type == ARG || (*segment).type == COMMAND)
		{
			while ((*segment).word[i])
			{
				tab_cmd[j] = ft_strdup((*segment).word[i]);
				j++;
				i++;
			}
		}
		i = 0;
		segment++;
	}
	return (tab_cmd);
}

static bool	fill_cmd(t_token *token, char **path, int size)
{
	if (path)
	{
		token->cmd->path_cmd = get_path_cmd(path, token->word[0]);
		free_tab((void **)path, 0);
	}
	token->cmd->tab_cmd = get_tab_cmd(token, size);
	if (!token->cmd->tab_cmd)
		return (false);
	return (true);
}

bool	get_cmds(t_token *segment, char **envp)
{
	char	**path;
	int		size;
	int		i;

	size = calculate_args(segment);
	i = 0;
	while (segment[i].type != END)
	{
		path = ft_split(get_path(envp), ':');
		if (!path)
			absolute_path(segment);
		if (segment[i].type == COMMAND)
		{
			if (!fill_cmd(&segment[i], path, size))
				return (false);
			break ;
		}
		i++;
	}
	return (true);
}

static void	absolute_path(t_token *token)
{
	if (ft_strchr(token->word[0], '/'))
	{
		if (!access(token->word[0], X_OK | F_OK))
			token->cmd->path_cmd = ft_strdup(token->word[0]);
		else
			token->cmd->path_cmd = NULL;
	}
}
