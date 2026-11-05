/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_check_next_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:44:05 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/13 17:58:22 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	check_next_char(char *src, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!src || !str || !*src || !*str)
		return ('!');
	while (src[i] == ' ')
		i++;
	if (!src[i])
		return ('!');
	while (str[j])
	{
		if (src[i] == str[j])
			return (str[j]);
		j++;
	}
	return ('\0');
}
