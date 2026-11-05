/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:02:18 by jbutte            #+#    #+#             */
/*   Updated: 2022/11/13 17:15:36 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	check_format(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%' )
		return (1);
	return (0);
}

int	type_to_print(va_list lst, char format)
{
	int	boolp;
	int	value;

	boolp = 1;
	value = 0;
	if (format == 'c')
		ft_putchar_printf(va_arg(lst, int), &value);
	else if (format == 's')
		ft_putstr_printf(va_arg(lst, char *), &value);
	else if (format == 'p')
		ft_putpointer_printf(va_arg(lst, unsigned long),
			"0123456789abcdef", &boolp, &value);
	else if (format == 'd' || format == 'i')
		ft_putnbr_printf(va_arg(lst, int), "0123456789", &value);
	else if (format == 'u')
		ft_putnbr_printf(va_arg(lst, unsigned int), "0123456789", &value);
	else if (format == 'x')
		ft_putnbr_printf(va_arg(lst, unsigned int), "0123456789abcdef", &value);
	else if (format == 'X')
		ft_putnbr_printf(va_arg(lst, unsigned int), "0123456789ABCDEF", &value);
	else if (format == '%')
		ft_putchar_printf('%', &value);
	return (value);
}

int	ft_printf(const char *format, ...)
{
	va_list	lst;
	int		index;	
	int		value;

	index = 0;
	value = 0;
	if (!format)
		return (0);
	va_start(lst, format);
	while (format[index])
	{
		if ((format[index] == '%') && check_format(format[index + 1]))
		{
			value += type_to_print(lst, format[index + 1]);
			index++;
		}
		else
			ft_putchar_printf(format[index], &value);
		index++;
	}
	va_end(lst);
	return (value);
}
