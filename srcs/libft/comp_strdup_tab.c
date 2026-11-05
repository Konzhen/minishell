/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_strdup_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:33:44 by jbutte            #+#    #+#             */
/*   Updated: 2023/03/07 16:30:42 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	**strdup_tab(char **tab)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		while (tab[i][j])
			j++;
		cpy[i] = ft_strdup(tab[i]);
		j = 0;
		i++;
	}
	return (cpy);
}
