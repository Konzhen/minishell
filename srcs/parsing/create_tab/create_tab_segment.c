/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_segment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:23:34 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:23:36 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*cut_line_for_segment(char *line, int *i)
{
	char	*segment;
	int		size;
	int		tmp;

	size = 0;
	skip_spaces(line, i);
	tmp = *i;
	while (line[*i] != '|' && line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			size += add_in_quotes(line, i);
		size++;
		(*i)++;
	}
	if (line[*i] == '|')
		(*i)++;
	segment = ft_calloc(size + 1, sizeof(char));
	if (!segment)
		return (NULL);
	ft_strlcpy(segment, &line[tmp], size + 1);
	return (segment);
}

static bool	fill_tab_segment(char *line, char **tab_segment, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < count)
	{
		tab_segment[j] = cut_line_for_segment(line, &i);
		if (!tab_segment[j])
			return (false);
		j++;
	}
	return (true);
}

char	**create_tab_segment(char *line, int count)
{
	char	**tab_segment;

	tab_segment = ft_calloc(count + 1, sizeof(char *));
	if (!tab_segment)
		return (NULL);
	if (!fill_tab_segment(line, tab_segment, count))
		return (NULL);
	return (tab_segment);
}
