/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:55:55 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:45:52 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fine_variable(char *str);

bool	var_is_in_env(t_env **p_envlst, char *variable)
{
	t_env	*p_tmp;
	char	*to_cmp;

	if (!p_envlst || !variable)
		return (false);
	p_tmp = *p_envlst;
	to_cmp = fine_variable(variable);
	while (p_tmp)
	{
		if (p_tmp && !ft_strcmp(p_tmp->variable, to_cmp))
		{
			free(to_cmp);
			return (true);
		}
		p_tmp = p_tmp->next;
	}
	if (to_cmp)
		free(to_cmp);
	return (false);
}

t_env	*get_variable(t_env **p_envlst, char *variable)
{
	t_env	*p_tmp;

	if (!p_envlst || !variable)
		return (NULL);
	p_tmp = *p_envlst;
	while (p_tmp)
	{
		if (!ft_strcmp(p_tmp->variable, variable))
			return (p_tmp);
		p_tmp = p_tmp->next;
	}
	return (NULL);
}

char	*get_value(t_env *p_variable)
{
	char	*copy;

	if (!p_variable || !p_variable->value)
		return (NULL);
	if (p_variable->value)
		copy = ft_strdup(p_variable->value);
	else
		copy = NULL;
	return (copy);
}

char	*fine_variable(char *str)
{
	char	*out;
	int		pos;

	pos = find_equal(str);
	if (pos && str[pos - 1] != '+')
		out = ft_substr(str, 0, pos);
	else
		out = ft_substr(str, 0, pos - 1);
	if (out)
		return (out);
	return (str);
}
