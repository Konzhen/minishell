/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:51:31 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:50:15 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PURPLE "\033[1;95m"
#define NC "\033[0m"

static void	zookshell_prompt(char *line, t_env **p_envlst);
static void	zshell_controlleur(char *line, t_env **env);

void	ft_read_input(char *line, char **env)
{
	t_env	*envlst;

	envlst = ft_env(env, -1);
	zshell_controlleur(line, &envlst);
	clean_fd();
	rl_clear_history();
	free(line);
	printf("\nexited from zouk successfuly\n");
	lst_destroy(envlst);
}

static void	zshell_controlleur(char *line, t_env **envlst)
{
	while (true)
	{
		set_signal();
		line = readline("\033[1;95mzouk_shell>\033[0m");
		if (line == NULL)
			break ;
		if (g_exit != -130)
		{
			if (*line == '\0')
				continue ;
			if (!check_valid_line(line))
				continue ;
			if (line)
				zookshell_prompt(line, envlst);
		}
		else
		{
			free(line);
			g_exit = 130;
		}
	}
}

static void	zookshell_prompt(char *line, t_env **p_envlst)
{
	t_token	**tab;

	add_history(line);
	tab = create_tab_to_exec(line, p_envlst);
	if (!tab)
		return ;
	open_files(tab, true);
	if (g_exit != -130)
	{
		do_expansion_all(tab, p_envlst);
		open_files(tab, false);
		if (running_managment(tab, p_envlst))
			tok_free(&tab);
	}
	else
	{
		g_exit = 130;
		clean_fd();
		tok_free(&tab);
	}
}
