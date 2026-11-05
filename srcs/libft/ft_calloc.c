/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:56:20 by jbutte            #+#    #+#             */
/*   Updated: 2023/02/27 16:29:27 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;

	if (!size || !nmemb)
	{
		tab = malloc(0);
		if (!tab)
			return (NULL);
		return (tab);
	}
	if ((nmemb * size) / nmemb != size)
		return (0);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (nmemb * size));
	return ((void *)tab);
}
