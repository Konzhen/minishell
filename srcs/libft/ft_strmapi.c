/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:08 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/20 16:19:44 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	unsigned int		size;
	char				*dest;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
