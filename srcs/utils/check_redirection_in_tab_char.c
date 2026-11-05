/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection_in_tab_char.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:08 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:41:10 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	check_redirection_in_tab_char(const char *tab_word)
{
	if (tab_word[0] == '<' || tab_word[0] == '>' || tab_word[0] == '|')
		return (1);
	return (0);
}
