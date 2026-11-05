/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_constructor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:39:01 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 17:56:46 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expanded_case(char **pmove, char **p_expd, t_token *token)
{
	char	*first_part;
	char	*cpy;

	if (token->expanded)
	{
		first_part = ft_strdup(token->expanded);
		free(token->expanded);
		cpy = ft_substr(*p_expd, 0, token->tool_len);
		token->expanded = ft_strjoin(first_part, cpy);
		multiple_freeing(cpy, first_part, NULL, NULL);
	}
	else if (ft_strcmp(token->word[0], "$?") != 0)
		token->expanded = ft_substr(token->word[0], 0, \
							ft_strlen(*p_expd) - ft_strlen(*pmove - 1));
}

static void	update_expanded_case(t_env **p_envlst, t_token *token)
{
	char	*first_part;
	char	*cpy;
	t_env	*node;

	first_part = ft_strdup(token->expanded);
	if (!first_part)
		return ;
	node = get_variable(p_envlst, token->tool_str);
	cpy = get_value(node);
	if (!cpy)
	{
		free(first_part);
		return ;
	}
	free(token->expanded);
	token->expanded = ft_strjoin(first_part, cpy);
	if (!token->expanded)
	{
		multiple_freeing(cpy, first_part, NULL, NULL);
		token->expanded = ft_strdup("");
		return ;
	}
	multiple_freeing(cpy, first_part, NULL, NULL);
}

char	*is_expand(t_env **penvlst, char **pmove, char **p_exp, t_token *token)
{
	size_t	len_to_exp;

	token->tool_len = (ft_strlen(*p_exp) - ft_strlen(*pmove));
	(*pmove)++;
	len_to_exp = ft_strspn(*pmove, \
		"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxy0123456789");
	token->tool_str = ft_substr(*pmove, 0, len_to_exp);
	if (var_is_in_env(penvlst, token->tool_str))
	{
		handle_expanded_case(pmove, p_exp, token);
		update_expanded_case(penvlst, token);
	}
	else
		handle_expanded_case(pmove, p_exp, token);
	*pmove += len_to_exp;
	*p_exp = *pmove;
	free(token->tool_str);
	token->tool_str = NULL;
	return (*pmove);
}

void	multiple_freeing(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	if (s3)
	{
		free(s3);
		s3 = NULL;
	}
	if (s4)
	{
		free(s4);
		s4 = NULL;
	}
}
