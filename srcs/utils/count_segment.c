/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:13 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:41:15 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	get_count_segment(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!add_in_quotes(line, &i))
				return (0);
			i++;
		}
		else if (line[i] == '|')
		{
			i++;
			if (!skip_spaces(line, &i))
				return (count);
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	count_segment(char *line)
{
	int	count;

	if (!skip_spaces(line, NULL))
		return (0);
	count = get_count_segment(line);
	return (count);
}
