/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:57:47 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:47:01 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_index(t_env **p_envlst);
static void	index_env(t_env **p_envlst, int *index);
static void	sort_env(t_env **p_envlst);

void	print_export(t_env **p_envlst)
{
	int		index;
	t_env	*p_tmp;

	index = 1;
	if (!p_envlst)
		return ;
	init_index(p_envlst);
	sort_env(p_envlst);
	p_tmp = *p_envlst;
	while (p_tmp)
	{
		if (index == p_tmp->index)
		{
			if (p_tmp->value)
				printf("declare -x %s=\"%s\"\n", p_tmp->variable, p_tmp->value);
			else if (p_tmp->print_export == true)
				printf("declare -x %s=\"\"\n", p_tmp->variable);
			else
				printf("declare -x %s\n", p_tmp->variable);
			index++;
			p_tmp = *p_envlst;
		}
		else
			p_tmp = p_tmp->next;
	}
}

static void	index_env(t_env **p_envlst, int *index)
{
	t_env	*p_tmp;
	t_env	*p_sorted;

	if (!p_envlst)
		return ;
	p_tmp = (*p_envlst)->next;
	p_sorted = *p_envlst;
	while (p_sorted && p_sorted->index)
		p_sorted = p_sorted->next;
	while (p_tmp)
	{
		if (!p_tmp->index && ft_strcmp(p_tmp->variable, p_sorted->variable) < 0)
			p_sorted = p_tmp;
		p_tmp = p_tmp->next;
	}
	p_sorted->index = *index;
}

static void	sort_env(t_env **p_envlst)
{
	t_env	*p_tmp;
	int		index;

	index = 1;
	if (!p_envlst)
		return ;
	p_tmp = *p_envlst;
	while (p_tmp)
	{
		index_env(p_envlst, &index);
		index++;
		p_tmp = p_tmp->next;
	}
}

static void	init_index(t_env **p_envlst)
{
	t_env	*p_tmp;

	if (!p_envlst)
		return ;
	p_tmp = *p_envlst;
	while (p_tmp)
	{
		p_tmp->index = 0;
		p_tmp = p_tmp->next;
	}
}
