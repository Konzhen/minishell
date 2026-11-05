/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:17:28 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/22 15:50:18 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	int				len;
	unsigned char	csrc;

	i = 0;
	csrc = c;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (csrc == s[i])
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
