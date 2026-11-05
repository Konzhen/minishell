/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_free_mtpstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:45:08 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/08 11:45:10 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_mtpstr(int nb_str, ...)
{
	va_list	lst;
	int		i;
	char	*str;

	if (!nb_str)
		return (0);
	va_start(lst, nb_str);
	i = 0;
	while (i < nb_str)
	{
		str = va_arg(lst, char *);
		free(str);
		i++;
	}
	va_end(lst);
	return (0);
}
