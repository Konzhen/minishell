/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:25:46 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/13 15:05:05 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && i < len)
	{
		while ((little[j] == big[i + j] && i + j < len) || little[j] == '\0')
		{
			if (little[j] == '\0' && big[i] && i < len)
				return ((char *)&big[i]);
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}
