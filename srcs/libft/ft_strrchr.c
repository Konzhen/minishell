/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:03 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/22 15:53:47 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	csrc;

	csrc = c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (csrc == s[i])
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
