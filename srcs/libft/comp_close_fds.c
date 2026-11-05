/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_close_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:05:25 by jbutte            #+#    #+#             */
/*   Updated: 2023/02/23 17:35:57 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	close_fds(int nb_fd, ...)
{
	va_list	lst;
	int		i;
	int		fd;

	if (!nb_fd)
		return (0);
	va_start(lst, nb_fd);
	i = 0;
	while (i < nb_fd)
	{
		fd = va_arg(lst, int);
		close(fd);
		i++;
	}
	va_end(lst);
	return (0);
}
