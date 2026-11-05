/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words_for_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:23:20 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:23:22 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static bool	check_redirection_in_segment(char *segment, int *i)
{	
	if (segment[*i] == '<' || segment[*i] == '>')
	{
		(*i)++;
		if (segment[*i] == segment[*i - 1])
			(*i)++;
		return (true);
	}
	return (false);
}

static bool	iterate_if_not_redirection(char *segment, int *i)
{
	while (segment[*i] != '<' && segment[*i] != '>' && segment[*i] != '|'
		&& segment[*i] != ' ' && segment[*i] != '\0')
	{
		if (segment[*i] == '\"' || segment[*i] == '\'')
			add_in_quotes(segment, i);
		(*i)++;
	}
	return (true);
}

static void	fill_cnt(char *segment, int *i)
{
	if (check_redirection_in_segment(segment, i))
		return ;
	else
		iterate_if_not_redirection(segment, i);
}

int	count_words_for_tab(char *segment)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	if (!segment || !*segment)
		return (0);
	while (segment[i])
	{
		if (segment[i] == ' ')
			i++;
		else
		{
			fill_cnt(segment, &i);
			cnt++;
		}
	}
	return (cnt);
}
