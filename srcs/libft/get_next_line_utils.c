/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:41:50 by jbutte            #+#    #+#             */
/*   Updated: 2022/11/02 14:56:09 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int				i;
	int				len;
	unsigned char	csrc;

	i = 0;
	csrc = c;
	len = ft_strlen_gnl(s) + 1;
	while (i < len && s[i])
	{
		if (s[i] == csrc)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char		*tab;
	size_t		bzero;

	bzero = 0;
	if (!size || !nmemb)
	{
		tab = malloc(0);
		if (!tab)
			return (NULL);
		return (tab);
	}
	if ((nmemb * size) / nmemb != size)
		return (0);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	while (bzero < nmemb)
	{
		tab[bzero] = '\0';
		bzero++;
	}
	return ((void *)tab);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*full;

	i = 0;
	j = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	full = ft_calloc_gnl(len + 1, sizeof(char));
	if (!full)
		return (NULL);
	while (s1 && s1[i])
	{
		full[i] = s1[i];
		i++;
	}
	free (s1);
	while (s2[j])
	{
		full[i + j] = s2[j];
		j++;
	}
	free (s2);
	full[i + j] = '\0';
	return (full);
}
