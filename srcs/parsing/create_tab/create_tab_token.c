/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:34:05 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:34:07 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	initialize_token(t_token *token)
{
	token->cmd = NULL;
	token->file = NULL;
	token->expanded = NULL;
	token->tool_str = NULL;
	token->word = NULL;
	token->double_quotes = false;
}

static bool	fill_tab_token(t_token *tab_token, char **tab_char,
		t_env **p_envlst)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (tab_char[i])
	{
		initialize_token(&tab_token[i]);
		if (check_redirection_in_tab_char(tab_char[i]))
		{
			if (!create_redir_token(&tab_token[i], tab_char[i]))
				return (false);
			i++;
			if (!create_file_token(&tab_token[i],
					tab_char[i], tab_token[i - 1], p_envlst))
				return (false);
		}
		else
			if (!create_exec_token(&tab_token[i], tab_char[i], &index))
				return (false);
		i++;
	}
	tab_token[i].type = END;
	return (true);
}

t_token	*create_tab_token(char **tab_char, t_env **p_envlst)
{
	t_token	*tab_token;
	int		count;

	count = tablen((void **)tab_char);
	tab_token = ft_calloc(count + 1, sizeof(t_token));
	if (!tab_token)
		return (NULL);
	if (!fill_tab_token(tab_token, tab_char, p_envlst))
	{
		free_tab((void **)tab_char, 0);
		return (NULL);
	}
	return (tab_token);
}
