/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:59:33 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/25 17:30:31 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *) s1;
	tmp2 = (unsigned char *) s2;
	i = 0;
	while (n)
	{
		n--;
		if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
		else if (tmp1[i] == '\0' && tmp2[i] != '\0')
			return (0 - tmp2[i]);
		else if (tmp2[i] == '\0' && tmp1[i] != '\0')
			return (tmp1[i]);
		i++;
	}
	return (0);
}
