/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_rmvchar_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:45:20 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/08 11:45:22 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	set_size_rmvchar(const char *src, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (src[i])
	{
		if (src[i] == c)
			i++;
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	*rmvchar_str(const char *src, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*dest;

	if (!src)
		return (NULL);
	i = 0;
	j = 0;
	size = set_size_rmvchar(src, c);
	dest = calloc2(size + 1, sizeof(char), "dest in rmvchar_str");
	while (src[i])
	{
		if (src[i] == c)
			i++;
		else
		{
			dest[j] = src[i];
			j++;
			i++;
		}
	}
	return (dest);
}
