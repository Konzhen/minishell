/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_free_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:05:38 by jbutte            #+#    #+#             */
/*   Updated: 2023/02/20 15:05:41 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	free_tab(void **tab, size_t size)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (1);
	if (size > 0)
	{
		while (i < size)
		{
			free(tab[i]);
			i++;
		}
	}
	else
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	tab = NULL;
	return (0);
}
