/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_between_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:15:26 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:57:13 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_between_quotes(bool *state, char c)
{
	static char	prev_c = '\0';

	if (*state == false)
		prev_c = '\0';
	if (prev_c == '\0' && (c == '\'' || c == '\"'))
		prev_c = c;
	if ((prev_c == '\0' || prev_c == '\'') && c == '\'')
		*state = !*state;
	if ((prev_c == '\0' || prev_c == '\"') && c == '\"')
		*state = !*state;
	return (state);
}
