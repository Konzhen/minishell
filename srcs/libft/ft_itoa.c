/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:28:24 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/25 18:54:23 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_itoaalloc(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_setsign(int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*ft_itoa(int n)
{
	int		nmb;
	char	*dest;
	int		sign;

	if (n == -2147483648)
	{
		dest = ft_strdup("-2147483648");
		return (dest);
	}
	nmb = ft_itoaalloc(n);
	dest = ft_calloc(nmb + 1, sizeof(char));
	if (!dest)
		return (NULL);
	sign = ft_setsign(&n);
	while (nmb)
	{
		nmb--;
		dest[nmb] = (n % 10) + 48;
		n /= 10;
	}
	if (sign == 1)
		dest[0] = '-';
	return (dest);
}
