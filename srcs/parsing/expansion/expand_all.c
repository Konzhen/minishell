/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:24:48 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 18:16:43 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_empty_expanded(t_token *token, char *tmp)
{
	if (!*token->expanded)
	{
		free(token->word[0]);
		token->word[0] = ft_strdup(token->expanded);
		return (true);
	}
	tmp = remove_quotes(token->expanded);
	if (!tmp)
		return (true);
	if (!*tmp)
	{
		free(token->word[0]);
		token->word[0] = ft_strdup(" ");
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

static bool	split_expanded(t_token *token)
{
	char	*tmp;
	char	**tab_char;

	tmp = NULL;
	if (check_empty_expanded(token, tmp))
		return (true);
	tab_char = create_tab_char(token->expanded);
	free(token->word[0]);
	free(token->word);
	token->tool_len = count_words_for_tab(token->expanded);
	token->word = ft_calloc(token->tool_len + 1, sizeof(char *));
	if (!token->word)
	{
		free(tmp);
		free_tab((void **)tab_char, 0);
		return (false);
	}
	if (!fill_token_word(token, tab_char))
	{
		free(tmp);
		return (false);
	}
	free(tmp);
	return (true);
}

static void	rework_tab_type(t_token **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (!tab[i][j].expanded && tab[i][j].type != END)
			j++;
		while (tab[i][j].type != END)
		{
			if (tab[i][j].type == COMMAND
				|| tab[i][j].type == BUILT_IN || tab[i][j].type == ARG)
				tab[i][j].type = is_builtin_expanded(&tab[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
}

void	do_expansion_all(t_token **token, t_env **p_envlst)
{
	char	*tmp_quote;
	size_t	index_up;
	size_t	index_deep;

	index_up = 0;
	index_deep = 0;
	while (token[index_up])
	{
		while (token[index_up][index_deep].type != END)
		{
			expansion(p_envlst, &token[index_up][index_deep]);
			if (token[index_up][index_deep].expanded)
				split_expanded(&token[index_up][index_deep]);
			else if (!token[index_up][index_deep].expanded)
			{
				tmp_quote = remove_quotes(token[index_up][index_deep].word[0]);
				free(token[index_up][index_deep].word[0]);
				token[index_up][index_deep].word[0] = tmp_quote;
			}
			index_deep++;
		}
		index_deep = 0;
		index_up++;
	}
	rework_tab_type(token);
}
