/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_err_cmd_bash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:43:29 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/08 11:43:37 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	err_cmd_bash(char *cmd)
{
	if (!cmd)
		return ;
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found", 2);
}
