/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:15:31 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 13:21:37 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	msg_exit_error(char *status, int *value)
{
	ft_putstr_fd("zouk_shell: exit: ", 2);
	ft_putstr_fd(status, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	*value = 1;
	return (false);
}
