/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:15:47 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/21 13:14:31 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	if (c != '\0' && c <= ' ')
		return (true);
	return (false);
}

static bool	is_delim(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i] != '\0')
	{
		if (c == delim[i])
			return (true);
		i++;
	}
	return (false);
}

static void	is_a_sep_next(char *line, char c, bool *error)
{
	if (line + 1)
		line++;
	while (*line && is_space(*line))
		line++;
	if ((c == '<' && (is_delim(*line, ">|") || !*line)))
		*error = true;
	if ((c == '>' && (is_delim(*line, "<|") || !*line)))
		*error = true;
	if ((c == '|' && (is_delim(*line, "|") || !*line)))
		*error = true;
}

bool	is_not_valid_syntax(char *line)
{
	int		i;
	bool	error;
	bool	state;

	i = 0;
	error = false;
	state = false;
	while (line[i])
	{
		is_between_quotes(&state, line[i]);
		if (line[i] == '<' && state == false)
			is_a_sep_next(&line[i], '<', &error);
		if (line[i] == '>' && state == false)
			is_a_sep_next(&line[i], '>', &error);
		if (line[i] == '|' && state == false)
			is_a_sep_next(&line[i], '|', &error);
		i++;
	}
	if (error)
	{
		ft_putstr_fd("zook_shell: syntax error near unexpected token\n", 2);
		g_exit = 2;
		return (true);
	}
	return (false);
}
