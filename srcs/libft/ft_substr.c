/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:43:39 by jbutte            #+#    #+#             */
/*   Updated: 2023/04/05 13:18:28 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		size;
	size_t		i;
	char		*dest;
	char		*str;

	size = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (len == 0 || start > ft_strlen(s))
	{
		str = ft_strdup("");
		return (str);
	}
	while (size < len && s[start + size] != '\0')
		size++;
	dest = ft_calloc((size + 1), sizeof(char));
	if (!dest)
		return (NULL);
	while (s[start] != '\0' && i < len)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
