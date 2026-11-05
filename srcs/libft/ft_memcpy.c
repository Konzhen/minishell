/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:30:55 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/22 15:57:40 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char				*tmpdest;
	char				*tmpsrc;
	size_t				i;

	tmpdest = (char *) dest;
	tmpsrc = (char *) src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		tmpdest[i] = tmpsrc[i];
		i++;
	}
	return ((void *)tmpdest);
}
