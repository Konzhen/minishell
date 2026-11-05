/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_closing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:53:57 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:49:43 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multi_closing(int a, int b, int c, int d)
{
	if (a >= 0)
		close(a);
	if (b >= 0)
		close(b);
	if (c >= 0)
		close(c);
	if (d >= 0)
		close(d);
}
