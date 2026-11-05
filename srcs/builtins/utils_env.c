/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:56:21 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:47:51 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_destroy(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
		node_destroy(tmp);
	}
	node_destroy(lst);
}

void	node_destroy(t_env *node)
{
	if (node->variable)
	{
		free(node->variable);
		node->variable = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
}
