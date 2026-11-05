/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:02 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/21 13:10:13 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	add_in_quotes(char *segment, int *i)
{
	int			size;
	char		tmp;

	size = 1;
	tmp = segment[*i];
	(*i)++;
	while (segment[*i] != tmp)
	{
		if (segment[*i] == '\0')
		{
			g_exit = 2;
			err_std(ERR_QUOTES_NOT_CLOSED);
			return (0);
		}
		size++;
		(*i)++;
	}
	return (size);
}
