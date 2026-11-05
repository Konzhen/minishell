/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:41:23 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:41:24 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_redirection	get_redirection_type(char *token_word)
{
	if (ft_strlen(token_word) == 2)
	{
		if (token_word[0] == '>' && token_word[1] == '>')
			return (APPEND_OUT);
		else if (token_word[0] == '<' && token_word[1] == '<')
			return (HEREDOC);
	}
	else if (ft_strlen(token_word) == 1)
	{
		if (token_word[0] == '>')
			return (OUT);
		else if (token_word[0] == '<')
			return (IN);
	}
	return (NOT_REDIR);
}
