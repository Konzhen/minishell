/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:10:33 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/16 09:13:33 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *) s1;
	tmp2 = (unsigned char *) s2;
	while (i < n)
	{
		if (tmp1[i] == '\0' || tmp2[i] == '\0')
			return (tmp1[i] - tmp2[i]);
		else if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
		i++;
	}
	return (0);
}
