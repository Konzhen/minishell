/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:55:19 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:46:46 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_plus_sign(char *str);
static void	append_var_in_env(t_env *p_node, char *str);
static void	set_value_to_var(t_env *p_node, char *str);
static bool	moving_strncmp(char *s1, char *s2);

void	modify_value_in_env(t_env **p_envlst, char *str)
{
	t_env	*p_tmp;
	char	*to_cmp;
	char	*tmp;

	if (!p_envlst || !str)
		return ;
	if (moving_strncmp(str, "+="))
	{
		to_cmp = fine_variable(str);
		tmp = remove_quotes (to_cmp);
		p_tmp = get_variable(p_envlst, tmp);
		append_var_in_env(p_tmp, str);
		free(tmp);
		free(to_cmp);
	}
	else
	{
		to_cmp = fine_variable(str);
		tmp = remove_quotes (to_cmp);
		p_tmp = get_variable(p_envlst, tmp);
		set_value_to_var(p_tmp, str);
		free(tmp);
		free(to_cmp);
	}
}

static void	set_value_to_var(t_env *p_node, char *str)
{
	int		pos;

	if (!p_node || !str)
		return ;
	pos = find_equal(str);
	if (!pos)
	{
		if (p_node && p_node->value)
		{
			free(p_node->value);
			p_node->value = NULL;
		}
	}
	if (p_node->value)
	{
		free(p_node->value);
		p_node->value = NULL;
	}
	if (pos)
	{
		p_node->value = ft_substr(str, pos + 1, (ft_strlen(str) - (pos + 1)));
		p_node->print_export = true;
		p_node->print_env = true;
	}
}

static void	append_var_in_env(t_env *p_node, char *str)
{
	int		pos;
	char	*copy;
	char	*adding_part;

	if (!p_node || !str)
		return ;
	pos = find_plus_sign(str);
	if (p_node->value)
	{
		copy = get_value(p_node);
		adding_part = ft_substr(str, pos + 2, (ft_strlen(str) - (pos + 2)));
		free(p_node->value);
		p_node->value = ft_strjoin(copy, adding_part);
		free(copy);
		free(adding_part);
	}
	else
		p_node->value = ft_substr(str, pos + 2, (ft_strlen(str) - (pos + 2)));
	p_node->print_export = true;
	p_node->print_env = true;
}

static int	find_plus_sign(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (-1);
	while (str[pos])
	{
		if (str[pos] == '+')
			return (pos);
		pos++;
	}
	return (0);
}

static bool	moving_strncmp(char *s1, char *s2)
{
	int	len;
	int	max_index;
	int	index;

	index = 0;
	if (!s1 || !s2)
		return (false);
	len = ft_strlen(s2);
	max_index = ft_strlen(s1) - len;
	while (index <= max_index)
	{
		if (!ft_strncmp(s1, s2, len))
			return (true);
		index++;
		s1++;
	}
	return (false);
}
