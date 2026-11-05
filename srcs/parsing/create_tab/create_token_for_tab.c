/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_for_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:34:12 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:34:19 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	create_file_token(t_token *token, char *tab_word,
		t_token redir, t_env **p_envlst)
{
	token->type = TFILE;
	if (!fill_token_file(token, tab_word, redir, p_envlst))
		return (false);
	token->word = ft_calloc(2, sizeof(char *));
	if (!token->word)
		return (false);
	token->word[0] = ft_strdup(tab_word);
	if (!token->word[0])
		return (false);
	return (true);
}

bool	create_redir_token(t_token *token, char *tab_word)
{
	token->type = REDIR;
	token->word = ft_calloc(2, sizeof(char *));
	if (!token->word)
		return (false);
	token->word[0] = ft_strdup(tab_word);
	if (!token->word[0])
		return (false);
	return (true);
}

bool	create_exec_token(t_token *token, char *tab_word, int *index)
{
	if (*index == 0)
		token->type = is_builtin(tab_word);
	else
		token->type = ARG;
	token->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!token->cmd)
		return (false);
	(*index)++;
	token->word = ft_calloc(2, sizeof(char *));
	if (!token->word)
		return (false);
	token->word[0] = ft_strdup(tab_word);
	if (!token->word[0])
		return (false);
	return (true);
}
