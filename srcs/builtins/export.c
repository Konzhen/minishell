/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:58:15 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:45:18 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_env(t_env **p_envlst, char **array, pid_t pid);
static char	*ivvn_error(char *str, int pid);

void	ft_export(t_env **p_envlst, char **array, pid_t pid)
{
	if (!p_envlst || !array)
		return ;
	while (*array && ft_strcmp(*array, "export"))
		array++;
	if (*(array + 1))
	{
		array++;
		while (*array)
		{
			if (*array && (!ft_strcmp(*array, "\"\"") || \
				!ft_strcmp(*array, "\'\'")))
				break ;
			add_to_env(p_envlst, array, pid);
			array++;
		}
	}
	else
		print_export(p_envlst);
}

static void	add_to_env(t_env **p_envlst, char **array, pid_t pid)
{
	t_env	*new;

	if (!p_envlst || !array)
		return ;
	if (*array && is_right_first_cara(*array))
	{
		if (var_is_in_env(p_envlst, *array) == false)
		{
			new = ft_node_creat(*array, pid);
			if (!new)
				return ;
			add_back_env(p_envlst, new);
		}
		else
			modify_value_in_env(p_envlst, *array);
	}
	else
	{
		if (!pid)
			exit (1);
		g_exit = 1;
		ft_putstr_fd("zook_shell: export: `", 2);
		ft_putstr_fd(*(array), 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
}

bool	is_right_first_cara(char *str)
{
	if (ft_isalpha(*str) || *str == '_')
		return (true);
	return (false);
}

char	*is_valid_var_name(char *str, int pos, pid_t pid)
{
	char	*output;
	size_t	len_check;
	size_t	out_len;

	out_len = 0;
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
	out_len = ft_strlen(output);
	if (out_len != len_check)
	{
		free(output);
		return (ivvn_error(str, pid));
	}
	else
		return (output);
}

static char	*ivvn_error(char *str, int pid)
{
	g_exit = 1;
	ft_putstr_fd("zook_shell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	if (!pid)
		exit (1);
	return (NULL);
}
