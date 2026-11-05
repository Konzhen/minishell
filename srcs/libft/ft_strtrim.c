/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:05:48 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/14 10:42:25 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_setindexstart(char const *s, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] != '\0' && s[i] != '\0')
	{
		if (s[i] != set[j])
				j++;
		else if (s[i] == set[j])
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int	ft_setindexend(char const *s, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s) - 1;
	j = 0;
	while (set[j] != '\0' && s[i] != '\0')
	{
		if (s[i] != set[j])
				j++;
		else if (s[i] == set[j])
		{
			i--;
			j = 0;
		}
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*dest;

	i = 0;
	if (!s || !set)
		return (NULL);
	start = ft_setindexstart(s, set);
	end = ft_setindexend(s, set);
	if (end < start)
	{
		dest = ft_strdup("");
		return (dest);
	}
	dest = ft_calloc(end - start + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (start < end)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	return (dest);
}
