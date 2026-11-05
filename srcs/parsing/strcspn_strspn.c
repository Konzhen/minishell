/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcspn_strspn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:15:59 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:57:22 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_delim(char c, char *delim);

size_t	ft_strcspn(char *s1, char *s2)
{
	size_t	len;

	len = 0;
	while (*s1 != '\0')
	{
		if (is_delim(*s1, s2) == true)
			return (len);
		len++;
		s1++;
	}
	return (len);
}

size_t	ft_strspn(char *s1, char *s2)
{
	size_t	len;

	len = 0;
	while (*s1 != '\0')
	{
		if (is_delim(*s1, s2) == false)
			return (len);
		len++;
		s1++;
	}
	return (len);
}

static bool	is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}
