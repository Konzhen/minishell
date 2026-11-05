/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_to_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:24:57 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:33:39 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static bool	fill_tab_to_exec(char **tab_segment,
		size_t i, t_env **p_envlst, t_token **tab_token)
{
	char	**tab_char;

	tab_char = create_tab_char(tab_segment[i]);
	if (!tab_char)
	{
		free_tab((void **)tab_char, 0);
		tok_free(&tab_token);
		return (false);
	}
	tab_token[i] = create_tab_token(tab_char, p_envlst);
	if (!tab_token[i])
	{
		free_tab((void **)tab_char, 0);
		tok_free(&tab_token);
		return (false);
	}
	free_tab((void **)tab_char, 0);
	return (true);
}

static t_token	**initialize_tab_to_exec(char **tab_segment,
		size_t count, t_env **p_envlst)
{
	size_t	i;
	t_token	**tab_token;

	i = 0;
	tab_token = ft_calloc(count + 1, sizeof(t_token *));
	if (!tab_token)
		return (NULL);
	while (i < count)
	{
		if (!fill_tab_to_exec(tab_segment, i, p_envlst, tab_token))
			return (NULL);
		i++;
	}
	free_tab((void **)tab_segment, 0);
	return (tab_token);
}

t_token	**create_tab_to_exec(char *line, t_env **p_envlst)
{
	int		count;
	char	**tab_segment;
	t_token	**tab_to_exec;

	count = count_segment(line);
	if (!count)
		return (NULL);
	tab_segment = create_tab_segment(line, count);
	if (!tab_segment)
		return (NULL);
	tab_to_exec = initialize_tab_to_exec(tab_segment, count, p_envlst);
	if (!tab_to_exec)
	{
		free_tab((void **)tab_to_exec, 0);
		return (NULL);
	}
	return (tab_to_exec);
}
