/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:04:23 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:47:39 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_node(t_env **p_envlst, char *str);
static void	suppressing_action(t_env *p_del, char *str);
static bool	is_not_valid_unset(char *str, int pos, pid_t pid);
static bool	invu_next(char *output, char *str, size_t len_check, pid_t pid);

void	unset(t_env **p_envlst, char **array)
{
	if (!p_envlst || !array)
		return ;
	while (*array && ft_strcmp(*array, "unset"))
		array++;
	if (*(array + 1))
		array++;
	while (*array)
	{
		del_node(p_envlst, *array);
		array++;
	}
	if (g_exit != 1)
		g_exit = 0;
}

void	del_node(t_env **p_envlst, char *str)
{
	t_env	*p_del;
	t_env	*p_prev;

	if (!p_envlst || !str)
		return ;
	p_prev = *p_envlst;
	p_del = *p_envlst;
	while (p_del)
	{
		if (ft_strcmp(str, p_del->variable) != 0)
		{
			p_prev = p_del;
			p_del = p_del->next;
		}
		else
			break ;
	}
	if (p_del == *p_envlst)
		*p_envlst = (*p_envlst)->next;
	else if (p_del && p_del->next)
		p_prev->next = p_del->next;
	else if (p_del && !ft_strcmp(str, p_del->variable))
		p_prev->next = NULL;
	suppressing_action(p_del, str);
}

static void	suppressing_action(t_env *p_del, char *str)
{
	if (p_del)
		node_destroy(p_del);
	if (is_not_valid_unset(str, 0, -1))
	{
		ft_putstr_fd("zook_shell: unset:`", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		g_exit = 1;
	}
}

static bool	is_not_valid_unset(char *str, int pos, pid_t pid)
{
	char	*output;
	size_t	len_check;

	len_check = 0;
	if (pos)
	{
		if (str[pos - 1] != '+')
			output = ft_substr(str, 0, pos);
		else
			output = ft_substr(str, 0, pos - 1);
	}
	else
		output = ft_strdup(str);
	len_check = ft_strspn(output, \
			"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxy0123456789");
	return (invu_next(output, str, len_check, pid));
}

static bool	invu_next(char *output, char *str, size_t len_check, pid_t pid)
{
	size_t	out_len;

	out_len = ft_strlen(output);
	if (out_len != len_check || !is_right_first_cara(str))
	{
		g_exit = 1;
		free(output);
		if (!pid)
			exit (1);
		return (true);
	}
	else
	{
		free(output);
		return (false);
	}
}
