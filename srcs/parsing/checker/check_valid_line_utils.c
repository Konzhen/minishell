/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:53:48 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:53:53 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *line, int *i)
{
	char	c;

	c = line[*i];
	(*i)++;
	while (line[*i] != c)
		(*i)++;
	(*i)++;
}
