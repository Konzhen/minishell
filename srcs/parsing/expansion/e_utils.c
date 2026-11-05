/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:15:14 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:55:31 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*choose_expansion(t_env **penvlst, char **pmove, char **p_exp, \
					t_token *token)
{
	if (*(*pmove + 1) == '?')
		*p_exp = expand_global(pmove, p_exp, token);
	else
		*p_exp = is_expand(penvlst, pmove, p_exp, token);
	return (*p_exp);
}
