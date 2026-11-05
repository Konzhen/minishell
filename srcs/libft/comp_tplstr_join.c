/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tplstr_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:45:41 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/08 11:45:49 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_join(char *full, const char *s)
{
	while (*s)
	{
		*full = *s;
		full++;
		s++;
	}
}

char	*tplstr_join(const char *s1, const char *s2, const char *s3)
{
	int		len;
	char	*full;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) +ft_strlen(s3);
	full = malloc(sizeof(char) * len + 1);
	if (!full)
		return (NULL);
	s_join(full, s1);
	s_join(full, s2);
	s_join(full, s3);
	*full = '\0';
	return (full);
}
