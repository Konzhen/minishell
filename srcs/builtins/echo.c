/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:35:51 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:43:51 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	echo_option(char *str);
static void	echo_newline(char **array);
static void	echo_no_newline(char **array);
static void	echo_exec(bool option, char **array, char **tmp);

void	echo(char **array)
{
	bool	move;
	bool	option;
	char	**tmp;

	move = true;
	option = false;
	if (!array)
		return ;
	while (*array && ft_strcmp(*array, "echo") != 0)
		array++;
	if (*array + 1 != NULL)
		array++;
	tmp = array;
	while (*tmp && **tmp == '-' && move)
	{
		move = echo_option(*tmp);
		option = echo_option(*array);
		if (move)
			tmp++;
	}
	echo_exec(option, array, tmp);
	g_exit = 0;
}

static void	echo_exec(bool option, char **array, char **tmp)
{
	if (option)
		echo_no_newline(tmp);
	else if (option == false)
		echo_newline(tmp);
	else
		echo_newline(array);
}

static bool	echo_option(char *str)
{
	bool	state;

	state = true;
	if (*(str + 1) == '\0')
		return (false);
	str++;
	while (*str)
	{
		if (*str == 'n')
			str++;
		else
		{
			state = false;
			break ;
		}
	}
	return (state);
}

static void	echo_newline(char **array)
{
	if (*array == NULL)
	{
		printf("\n");
		return ;
	}
	while (*array)
	{
		if (*(array + 1) != NULL)
			printf("%s ", *array);
		else
			printf("%s\n", *array);
		array++;
	}
}

static void	echo_no_newline(char **array)
{
	while (*array)
	{
		if (*(array + 1) != NULL)
		{
			ft_putstr_fd(*array, 1);
			ft_putstr_fd(" ", 1);
		}
		else
			ft_putstr_fd(*array, 1);
		array++;
	}
}
