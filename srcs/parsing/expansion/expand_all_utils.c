/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:21:46 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:22:22 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static bool	check_builtin(char *word, size_t size)
{
	if ((!ft_strncmp(word, "pwd", size)
			&& size == ft_strlen("pwd"))
		|| (!ft_strncmp(word, "cd", size)
			&& size == ft_strlen("cd"))
		|| (!ft_strncmp(word, "export", size)
			&& size == ft_strlen("export"))
		|| (!ft_strncmp(word, "echo", size)
			&& size == ft_strlen("echo"))
		|| (!ft_strncmp(word, "exit", size)
			&& size == ft_strlen("exit"))
		|| (!ft_strncmp(word, "unset", size)
			&& size == ft_strlen("unset"))
		|| (!ft_strncmp(word, "env", size)
			&& size == ft_strlen("env")))
		return (true);
	return (false);
}

t_enum_type	is_builtin_expanded(t_token *token)
{
	size_t	size;

	size = ft_strlen(token->word[0]);
	if (!size)
	{
		if (token->expanded)
			return (ERROR);
		else
			return (COMMAND);
	}
	if (check_builtin(token->word[0], size))
		return (BUILT_IN);
	return (COMMAND);
}

bool	fill_token_word(t_token *token, char **tab_char)
{
	int		i;

	i = 0;
	while (tab_char[i])
	{
		token->word[i] = remove_quotes(tab_char[i]);
		if (!token->word[i])
		{
			free_tab((void **)tab_char, 0);
			return (false);
		}
		i++;
	}
	free_tab((void **)tab_char, 0);
	return (true);
}
