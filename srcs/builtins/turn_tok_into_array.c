/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_tok_into_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:25 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 14:07:50 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		eb_next(char **towork, char *str);

bool	e_builtin(char **towork, char *str, t_env **p_envlst, pid_t pid)
{
	if (!ft_strcmp(str, "cd"))
		ft_cd(p_envlst, towork, pid);
	else if (!ft_strcmp(str, "unset"))
		unset(p_envlst, towork);
	else if (!ft_strcmp(str, "export"))
		ft_export(p_envlst, towork, pid);
	else if (!ft_strcmp(str, "env"))
		ft_print_env(p_envlst);
	else if (!ft_strcmp(str, "echo"))
		echo(towork);
	else if (!ft_strcmp(str, "exit"))
	{
		free(str);
		str = NULL;
		return (ft_exit(towork, p_envlst));
	}
	return (eb_next(towork, str));
}

static bool	eb_next(char **towork, char *str)
{
	if (towork != NULL)
	{
		free_tab((void **)towork, 0);
		towork = NULL;
	}
	free(str);
	str = NULL;
	return (true);
}

char	**turn_tok_into_array(t_token **segment, int index_up)
{
	char		**array;
	t_tta_tool	tool;

	if (!segment)
		return (NULL);
	setup_ttia(&tool, segment, index_up);
	array = malloc(sizeof(char *) * (tool.len + 1));
	if (!array)
		return (NULL);
	while (segment[index_up][tool.i].type != END)
	{
		if (segment[index_up][tool.i].type != ERROR && \
			segment[index_up][tool.i].type != TFILE \
		&& segment[index_up][tool.i].type != REDIR)
		{
			if (clean_fill_array(array, &tool, segment, index_up) == false)
				return (NULL);
		}
		tool.i++;
	}
	array[tool.j] = NULL;
	return (array);
}
