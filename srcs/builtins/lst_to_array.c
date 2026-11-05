/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:01:08 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:46:33 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_array_to_execve(t_env **p_envlst, char **array);
static void	handle_case_value(char *str, char **array, char *tool_str);
static void	handle_case_no_value(char **array, char *tool_str);

char	**lst_to_array(t_env **p_envlst)
{
	char	**array;
	t_env	*pmove;
	size_t	len;

	len = 0;
	array = NULL;
	if (!p_envlst || !(*p_envlst))
	{
		ft_putstr_fd("env delete\n", 2);
		return (NULL);
	}
	pmove = *p_envlst;
	while (pmove)
	{
		len++;
		pmove = pmove->next;
	}
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	create_array_to_execve(p_envlst, array);
	return (array);
}

static void	create_array_to_execve(t_env **p_envlst, char **array)
{
	t_env	*pmove;
	char	*tool_str;

	pmove = *p_envlst;
	while (pmove)
	{
		tool_str = ft_strdup(pmove->variable);
		if (pmove->value)
			handle_case_value(pmove->value, array, tool_str);
		else
			handle_case_no_value(array, tool_str);
		pmove = pmove->next;
		array++;
	}
	*array = NULL;
}

static void	handle_case_value(char *str, char **array, char *tool_str)
{
	*array = ft_strjoin(tool_str, "=");
	if (!*array)
		return ;
	free(tool_str);
	tool_str = ft_strdup(*array);
	if (!*tool_str)
	{
		free(array);
		return ;
	}
	free(*array);
	*array = ft_strjoin(tool_str, str);
	if (!*array)
	{
		free(tool_str);
		return ;
	}
	free(tool_str);
	tool_str = NULL;
}

static void	handle_case_no_value(char **array, char *tool_str)
{
	*array = ft_strjoin(tool_str, "=");
	if (!*array)
		return ;
	free(tool_str);
	tool_str = NULL;
}
