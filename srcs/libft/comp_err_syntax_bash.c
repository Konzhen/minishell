/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_err_syntax_bash.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:44:30 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/09 08:21:20 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	err_syntax_bash(char *cmd)
{
	if (!cmd)
		return ;
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\'\n", 2);
}
