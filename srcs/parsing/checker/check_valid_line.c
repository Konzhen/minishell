/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:53:33 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 17:27:33 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_char_after_redir(char *tmp, char *line)
{
	if (check_next_char(line, "><|") == '!')
		return (*tmp);
	*tmp = check_next_char(line, "><|");
	if (*tmp)
		return (*tmp);
	return ('\0');
}

static char	check_unexpected_redir(char *line, int *i)
{
	char	tmp;

	tmp = line[*i];
	(*i)++;
	if (!line[*i])
		return (line[*i - 1]);
	if ((line[*i - 1] == '<' && line[*i] == '>')
		|| (line[*i - 1] == '>' && line[*i] == '<') || line[*i] == '|')
		return (line[*i]);
	else if (line[*i] == ' ')
	{
		if (check_char_after_redir(&tmp, &line[*i]))
			return (tmp);
	}
	else if (line[*i] == tmp)
	{
		(*i)++;
		if (check_char_after_redir(&tmp, &line[*i]))
			return (tmp);
	}
	return ('\0');
}

static bool	check_quotes(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			if (!add_in_quotes(line, &i))
				return (false);
		i++;
	}
	return (true);
}

static char	check_overall(char *line)
{
	int		i;
	char	err;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quotes(line, &i);
		else if (line[i] == '>' || line[i] == '<')
		{
			err = check_unexpected_redir(line, &i);
			if (err)
				return (err);
		}
		else if (line[i] == '|')
		{
			i++;
			if (check_next_char(&line[i], "|"))
				return ('|');
		}
		else
			i++;
	}
	return ('\0');
}

bool	check_valid_line(char *line)
{
	int		i;
	char	err;

	i = 0;
	while (line[i] == ' ' || (line[i] <= 13 && line[i] >= 7))
		i++;
	if (!line[i])
		return (false);
	if (line[i] == '|')
	{
		g_exit = 2;
		err_syntax_bash("|");
		return (false);
	}
	if (!check_quotes(line))
		return (false);
	err = check_overall(line);
	if (err)
	{
		g_exit = 2;
		err_syntax_bash(&err);
		return (false);
	}
	return (true);
}
