/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:55:42 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 14:27:15 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exit_param(char **status, t_env **p_envlst);
static int	checking_parameter(char **status, int *value);
static bool	checking_first_para(char *status, int *value);
static bool	overflow_param(char *status, int *value);

bool	ft_exit(char **status, t_env **p_envlst)
{
	if (!status)
		return (false);
	while (ft_strcmp(*status, "exit"))
		status++;
	if (*(status + 1) == NULL)
	{
		printf("exited from zouk successfully\n");
		lst_destroy(*p_envlst);
		free_tab((void **)status, 0);
		status = NULL;
		exit(g_exit % 256);
	}
	else
		return (exit_param(status, p_envlst));
}

static bool	exit_param(char **status, t_env **p_envlst)
{
	int	value;
	int	check;

	value = 0;
	status++;
	check = checking_parameter(status, &value);
	status--;
	free_tab((void **)status, 0);
	status = NULL;
	if (check == -1)
	{
		g_exit = 1;
		return (false);
	}
	else
	{
		ft_putstr_fd("exited from zouk successfully\n", 1);
		lst_destroy(*p_envlst);
		exit (value % 256);
	}
}

static int	checking_parameter(char **status, int *value)
{
	bool	state;

	state = checking_first_para(*status, value);
	if (*(status + 1) && state == true)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("zook_shell: exit: too many arguments\n", 2);
	}
	if (state == true && *(status + 1) == NULL)
	{
		*value = ft_atoi(*status);
		return (0);
	}
	else if (state == false)
	{
		*value = 2;
		return (0);
	}
	else
		*value = 1;
	return (-1);
}

static bool	checking_first_para(char *status, int *value)
{
	int	len;
	int	index;

	index = 0;
	if (!status)
		return (true);
	len = ft_strlen(status);
	if (len > 19 || (len == 19 && ft_strcmp("9223372036854775807", status) < 0))
		return (overflow_param(status, value));
	if ((status[index] == '-' || status[index] == '+') \
		&& status[index + 1] != '\0')
		index++;
	while (index < len)
	{
		if (ft_isalpha(status[index]) || status[index] == '+' || \
			status[index] == '-')
			break ;
		index++;
	}
	if (index != len || (index == len && ft_isalpha(status[0])))
		return (msg_exit_error(status, value));
	return (true);
}

static bool	overflow_param(char *status, int *value)
{
	*value = 1;
	ft_putstr_fd(status, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (false);
}
