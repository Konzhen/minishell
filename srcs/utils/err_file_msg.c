/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_file_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:18 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:41:20 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	err_file_msg(char *name, bool is_valid_name)
{
	ft_putstr_fd("zook_shell: ", 2);
	ft_putstr_fd(name, 2);
	if (!is_valid_name)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
	g_exit = 1;
}
