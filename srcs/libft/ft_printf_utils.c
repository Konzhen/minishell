/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:10:42 by jbutte            #+#    #+#             */
/*   Updated: 2022/11/13 17:00:16 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putchar_printf(char c, int *value)
{
	write(1, &c, 1);
	*value += 1;
}

void	ft_putstr_printf(char *s, int *value)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		*value += 6;
		return ;
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
		*value += 1;
	}
}

void	ft_putnbr_printf(long int n, char *base, int *value)
{
	int	len;

	len = ft_strlen(base);
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		*value += 1;
	}
	if (n >= len)
		ft_putnbr_printf(n / len, base, value);
	ft_putchar_printf(base[n % len], value);
}

void	ft_putpointer_printf(unsigned long n, char *base,
		int *boolp, int *value)
{
	unsigned long	len;

	len = ft_strlen(base);
	if (n == 0)
	{
		write(1, "(nil)", 5);
		*value += 5;
		return ;
	}
	if (*boolp)
	{
		write(1, "0x", 2);
		*value += 2;
		*boolp = 0;
	}
	if (n >= len)
		ft_putpointer_printf(n / len, base, boolp, value);
	ft_putchar_printf(base[n % len], value);
}
