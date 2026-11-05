/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:37:13 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 18:08:56 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*not_expand(t_env **env, char **pmove, char **p_exp, t_token *tok);
static char	*do_expansion(t_env **env, char **pmove, char **p_exp, t_token *tk);
static void	glue_the_last_part(char **p_expand, t_token *token);

void	expansion(t_env **p_envlst, t_token *token)
{
	char	*p_to_move;
	char	*p_expand;

	if (!token->word[0])
		return ;
	p_to_move = token->word[0];
	p_expand = token->word[0];
	while (*p_to_move)
	{
		if ((*p_to_move == '\'' || *p_to_move == '\"') \
			&& *(p_to_move + 1) != '\0')
		{
			p_to_move = not_expand(p_envlst, &p_to_move, &p_expand, token);
			continue ;
		}
		else if (*p_to_move == '$' && *(p_to_move + 1) != '\0')
		{
			p_expand = choose_expansion(p_envlst, &p_to_move, &p_expand, token);
			continue ;
		}
		if (*p_to_move)
			p_to_move++;
	}
	if (token->expanded && p_expand != token->word[0])
		glue_the_last_part(&p_expand, token);
}

char	*expand_global(char **pmove, char **p_expand, t_token *token)
{
	char	*first_part;
	char	*cpy;

	first_part = NULL;
	++(*pmove);
	handle_expanded_case(pmove, p_expand, token);
	if (token->expanded)
		first_part = ft_strdup(token->expanded);
	else
		first_part = ft_strdup("");
	cpy = ft_itoa(g_exit % 256);
	free(token->expanded);
	token->expanded = ft_strjoin(first_part, cpy);
	if (!token->expanded)
	{
		free(cpy);
		free(first_part);
		return (NULL);
	}
	free(first_part);
	free(cpy);
	*pmove += 1;
	*p_expand = *pmove;
	return (*pmove);
}

static void	glue_the_last_part(char **p_expand, t_token *token)
{
	char	*p_to_move;
	char	*cpy;

	cpy = NULL;
	p_to_move = ft_strdup(*p_expand);
	if (*token->expanded != '\0')
		cpy = ft_strdup(token->expanded);
	free(token->expanded);
	if (cpy)
		token->expanded = ft_strjoin(cpy, p_to_move);
	else
		token->expanded = ft_strdup(p_to_move);
	free(cpy);
	free(p_to_move);
}

static char	*not_expand(t_env **env, char **pmove, char **p_exp, t_token *token)
{
	char	which_q;
	char	*pos_quote;
	char	*pos_dollar;
	size_t	len_quote;
	size_t	len_dollar;

	token->double_quotes = true;
	len_quote = 0;
	len_dollar = 0;
	which_q = **pmove;
	pos_quote = ft_strchr(++(*pmove), which_q);
	pos_dollar = ft_strchr(*pmove, '$');
	if (pos_quote)
		len_quote = ft_strlen(pos_quote);
	if (pos_dollar)
		len_dollar = ft_strlen(pos_dollar);
	if (!len_quote || !len_dollar)
		return (*pmove);
	if (len_quote > len_dollar)
	{
		*pmove += ft_strlen(*pmove) - len_quote + 1;
		return (*pmove);
	}
	else
		return (do_expansion(env, pmove, p_exp, token));
}

static char	*do_expansion(t_env **env, char **pmove, char **p_exp, t_token *tok)
{
	size_t	skip;
	char	delim[2];

	delim[1] = '\0';
	--(*pmove);
	if (**pmove == '\'')
	{
		delim[0] = '\'';
		skip = ft_strcspn(++(*pmove), delim);
		*pmove += skip + 1;
		return (*pmove);
	}
	else if (**pmove == '\"')
	{
		delim[0] = '$';
		skip = ft_strcspn(++(*pmove), delim);
		*pmove += skip;
		return (is_expand(env, pmove, p_exp, tok));
	}
	else
		return (is_expand(env, pmove, p_exp, tok));
}
