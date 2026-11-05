/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:48:57 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:44:08 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hnc_with_out_pos(t_env *new, size_t pos, char *str, pid_t pid);

static void	handle_node_case(t_env *new, size_t pos, char *str, pid_t pid)
{
	if (pos && str[pos + 1] != '\0')
	{
		new->variable = is_valid_var_name(str, pos, pid);
		if (!new->variable)
			return ;
		new->print_export = true;
		new->value = ft_substr(str, pos + 1, (ft_strlen(str) - (pos + 1)));
		if (!new->value)
			return ;
	}
	else if (pos && str[pos + 1] == '\0')
	{
		new->variable = is_valid_var_name(str, pos, pid);
		if (!new->variable)
			return ;
		new->value = NULL;
		new->print_export = true;
	}
	else
		hnc_with_out_pos(new, pos, str, pid);
}

static void	hnc_with_out_pos(t_env *new, size_t pos, char *str, pid_t pid)
{
	new->variable = is_valid_var_name(str, pos, pid);
	if (!new->variable)
		return ;
	new->value = NULL;
	new->print_export = false;
}

t_env	*ft_node_creat(char *str, pid_t pid)
{
	t_env		*new;
	size_t		pos;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	pos = find_equal(str);
	handle_node_case(new, pos, str, pid);
	if (!new->variable)
	{
		free(new);
		return (NULL);
	}
	if (new->value)
		new->print_env = true;
	else
		new->print_env = false;
	new->index = 0;
	new->next = NULL;
	return (new);
}

t_env	*ft_env(char **envp, pid_t pid)
{
	t_env	*envlst;
	t_env	*node;
	int		index;

	envlst = NULL;
	index = 0;
	while (envp[index])
	{
		node = ft_node_creat(envp[index], pid);
		if (!node)
			return (NULL);
		add_back_env(&envlst, node);
		index++;
	}
	return (envlst);
}
