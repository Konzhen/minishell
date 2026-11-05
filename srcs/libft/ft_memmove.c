/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:02:46 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/25 17:33:12 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char				*tmpdest;
	const char			*tmpsrc;

	tmpdest = (char *) dest;
	tmpsrc = (const char *) src;
	if (!dest && !src)
		return (0);
	if (dest > src)
	{
		while (n)
		{
			n--;
			tmpdest[n] = tmpsrc[n];
		}
		return (dest);
	}
	else
	{
		ft_memcpy(tmpdest, tmpsrc, n);
		return (dest);
	}
	return (NULL);
}
