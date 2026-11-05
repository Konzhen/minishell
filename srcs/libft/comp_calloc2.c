/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_calloc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:08:33 by jbutte            #+#    #+#             */
/*   Updated: 2023/02/28 14:08:36 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	err_std_calloc2(char *msg)
{
	write(2, "Error\n", 6);
	ft_putstr_fd("malloc of ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" failed", 2);
}

void	*calloc2(size_t nmemb, size_t size, char *msg)
{
	char	*tab;

	if (!size || !nmemb)
	{
		tab = malloc(0);
		if (!tab)
		{
			err_std_calloc2(msg);
			return (NULL);
		}
		return (tab);
	}
	if ((nmemb * size) / nmemb != size)
		return (0);
	tab = malloc(nmemb * size);
	if (!tab)
	{
		err_std_calloc2(msg);
		return (NULL);
	}
	ft_bzero(tab, (nmemb * size));
	return ((void *)tab);
}
