/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:23:46 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:23:49 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*add_redirection(char *segment, int *i)
{
	char	*str;
	int		size;
	int		i_bis;

	size = 0;
	i_bis = *i;
	if (segment[*i] == '<' || segment[*i] == '>')
	{
		if (segment[*i] == segment[*i + 1])
		{
			size++;
			(*i)++;
		}
	}
	size++;
	(*i)++;
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &segment[i_bis], size + 1);
	return (str);
}

static char	*add_alpha(char *segment, int *i)
{
	char	*str;
	int		size;
	int		i_bis;

	size = 0;
	i_bis = *i;
	while (segment[*i] != '<' && segment[*i] != '>' && segment[*i] != '|'
		&& segment[*i] != ' ' && segment[*i] && segment[*i] != '\0')
	{
		if (segment[*i] == '\"' || segment[*i] == '\'')
			size += add_in_quotes(segment, i);
		size++;
		(*i)++;
	}
	str = ft_calloc(size + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &segment[i_bis], size + 1);
	return (str);
}

static char	*fill_pchar(char *segment, int *i)
{
	char	*str;

	if (segment[*i] == '<' || segment[*i] == '>')
	{
		str = add_redirection(segment, i);
		if (!str)
			return (NULL);
	}
	else
	{
		str = add_alpha(segment, i);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	**create_tab_char(char *segment)
{
	int		size;
	char	**tab;
	int		i;
	int		j;

	size = count_words_for_tab(segment);
	tab = ft_calloc(size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size)
	{
		if (segment[i] == ' ')
			i++;
		else
		{
			tab[j] = fill_pchar(segment, &i);
			if (!tab[j])
				return (NULL);
			j++;
		}
	}
	return (tab);
}
