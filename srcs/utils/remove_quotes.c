/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:28 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:41:30 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	set_size_rm_quotes(const char *word)
{
	size_t	i;
	size_t	size;
	char	c;

	i = 0;
	size = 0;
	while (word[i])
	{
		if (word[i] == '\"' || word[i] == '\'')
		{
			c = word[i];
			i++;
			while (word[i] != c)
			{
				size++;
				i++;
			}
		}
		else
			size++;
		i++;
	}
	return (size);
}

static void	fill_str_without_quotes(const char *word,
		char *cl_word)
{
	int		i;
	char	c;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			c = word[i];
			i++;
			while (word[i] != c)
			{
				*cl_word = word[i];
				i++;
				cl_word++;
			}
			i++;
		}
		else
		{
			*cl_word = word[i];
			cl_word++;
			i++;
		}
	}
}

char	*remove_quotes(const char *word)
{
	char	*cl_word;
	size_t	size;

	if (!word || !*word)
		return (NULL);
	size = set_size_rm_quotes(word);
	cl_word = ft_calloc(size + 1, sizeof(char));
	if (!cl_word)
		return (NULL);
	fill_str_without_quotes(word, cl_word);
	return (cl_word);
}
