/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:39:09 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/08 15:36:14 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	char			*cpy;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
