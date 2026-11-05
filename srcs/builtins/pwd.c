/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:54:45 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:47:09 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*buffer;
	size_t	buffer_size;

	buffer = NULL;
	buffer_size = 0;
	buffer = getcwd(buffer, buffer_size);
	if (buffer == NULL)
	{
		perror("pwd :");
		g_exit = 1;
		return ;
	}
	printf("%s\n", buffer);
	free(buffer);
	return ;
}
