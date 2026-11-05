/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tablen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:46:08 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/08 11:46:18 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	tablen(void **tab)
{
	size_t	size;

	if (!tab || !*tab)
		return (0);
	size = 0;
	while (tab[size])
		size++;
	return (size);
}
