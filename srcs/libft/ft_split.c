/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:09:16 by jbutte            #+#    #+#             */
/*   Updated: 2023/01/30 17:31:16 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_cntwrd(char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			if (s[i + 1] == c || (s[i + 1] == '\0' && s[i] != c))
				words++;
			i++;
		}
	}
	return (words);
}

static char	*ft_putwrd(const char *s, char c, int *i)
{
	int		len;
	int		start;
	char	*str;

	start = 0;
	len = 0;
	str = NULL;
	while (s[*i] == c && s[*i])
		(*i)++;
	start = *i;
	while (s[*i] != c && s[*i])
	{
		len++;
		if (s[*i + 1] == c || (s[*i + 1] == '\0' && s[*i] != c))
		{
			str = ft_substr(s, start, len);
		}
		(*i)++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		words;
	int		wordscnt;
	char	**str;

	i = 0;
	words = 0;
	if (!s)
		return (NULL);
	wordscnt = ft_cntwrd(s, c);
	str = malloc(sizeof(char *) * (wordscnt + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[words] = ft_putwrd(s, c, &i);
		if (str[words])
			words++;
	}
	str[words] = NULL;
	return (str);
}
