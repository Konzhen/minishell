/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:57:10 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:44:20 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envlstlast(t_env *lst)
{
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_back_env(t_env **lst, t_env *node)
{
	if ((*lst) == NULL)
		*lst = node;
	else
		envlstlast(*lst)->next = node;
}

int	find_equal(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (-1);
	while (str[pos])
	{
		if (str[pos] == '=')
			return (pos);
		pos++;
	}
	return (0);
}
