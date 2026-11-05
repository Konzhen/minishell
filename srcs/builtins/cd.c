/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:44:58 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:40:29 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	modify_pwd(t_env **lst);
static void	modify_old_pwd(t_env **lst);
static int	particular_cd(t_env **lst, char **str);
static void	glue_value(t_env *tmp, char *copy);

void	ft_cd(t_env **lst, char **str, pid_t pid)
{
	int		result;

	if (!str)
		return ;
	if (*(str + 1) == NULL || !ft_strcmp((*(str + 1)), "-"))
		result = particular_cd(lst, str);
	else
		result = chdir(*(str + 1));
	if (result < 0)
	{
		if (result != -2)
			perror(*(str + 1));
		g_exit = 1;
		if (!pid)
			exit (1);
		return ;
	}
	modify_old_pwd(lst);
	modify_pwd(lst);
}

static int	particular_cd(t_env **lst, char **str)
{
	int		result;
	t_env	*cd_home;

	result = 0;
	if (*(str + 1) == NULL)
	{
		cd_home = get_variable(lst, "HOME");
		if (!cd_home)
		{
			ft_putstr_fd("zook_shell: cd: HOME not set\n", 2);
			return (-2);
		}
		result = chdir(cd_home->value);
	}
	else if (!ft_strcmp((*(str + 1)), "-"))
	{
		cd_home = get_variable(lst, "OLDPWD");
		if (!cd_home)
			return (-2);
		result = chdir(cd_home->value);
	}
	return (result);
}

static void	modify_old_pwd(t_env **lst)
{
	t_env	*tmp;
	char	*copy;

	tmp = *lst;
	copy = NULL;
	while (tmp && ft_strcmp(tmp->variable, "PWD"))
		tmp = tmp->next;
	if (tmp)
	{
		if (tmp->value)
		{
			copy = ft_strdup(tmp->value);
			free(tmp->value);
		}
	}
	tmp = *lst;
	while (tmp && ft_strcmp(tmp->variable, "OLDPWD"))
		tmp = tmp->next;
	if (tmp && copy)
		glue_value(tmp, copy);
	else if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup("");
	}
}

static void	glue_value(t_env *tmp, char *copy)
{
	free(tmp->value);
	tmp->value = ft_strdup(copy);
	free(copy);
}

static void	modify_pwd(t_env **lst)
{
	t_env	*tmp;
	char	*buffer;
	size_t	buffer_size;

	buffer_size = 0;
	buffer = NULL;
	tmp = *lst;
	while (tmp && ft_strcmp(tmp->variable, "PWD"))
		tmp = tmp->next;
	if (!tmp)
		return ;
	buffer = getcwd(buffer, buffer_size);
	if (!ft_strcmp(buffer, ""))
	{
		free (buffer);
		return ;
	}
	if (tmp)
	{
		tmp->value = ft_strdup(buffer);
		free(buffer);
	}
}
