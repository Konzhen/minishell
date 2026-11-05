/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:52:46 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/20 16:17:31 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*tmp;

	cc = (unsigned char) c;
	i = 0;
	tmp = (unsigned char *) s;
	while (i < n)
	{
		if (tmp[i] == cc)
			return ((void *)&tmp[i]);
		i++;
	}
	return (NULL);
}
