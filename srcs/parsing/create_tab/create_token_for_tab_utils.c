/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_for_tab_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:34:32 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:34:34 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*expand_file(char *tab_word, t_env **p_envlst)
{
	t_token	*tmp;
	char	*cpy;

	tmp = ft_calloc(sizeof(t_token), 1);
	tmp->word = ft_calloc(sizeof(char *), 2);
	tmp->word[0] = ft_strdup(tab_word);
	expansion(p_envlst, tmp);
	if (tmp->expanded)
	{
		cpy = ft_strdup(tmp->expanded);
		free(tmp->expanded);
	}
	else
		cpy = remove_quotes(tmp->word[0]);
	free(tmp->word[0]);
	free(tmp->word);
	free(tmp);
	return (cpy);
}

t_enum_type	is_builtin(char *token_word)
{
	char	*tmp;
	size_t	size;

	tmp = remove_quotes(token_word);
	size = ft_strlen(tmp);
	if ((!ft_strncmp(tmp, "pwd", size) && size == ft_strlen("pwd"))
		|| (!ft_strncmp(tmp, "cd", size) && size == ft_strlen("cd"))
		|| (!ft_strncmp(tmp, "export", size) && size == ft_strlen("export"))
		|| (!ft_strncmp(tmp, "echo", size) && size == ft_strlen("echo"))
		|| (!ft_strncmp(tmp, "exit", size) && size == ft_strlen("exit"))
		|| (!ft_strncmp(tmp, "unset", size) && size == ft_strlen("unset"))
		|| (!ft_strncmp(tmp, "env", size) && size == ft_strlen("env")))
	{
		free(tmp);
		return (BUILT_IN);
	}
	free(tmp);
	return (COMMAND);
}

bool	fill_token_file(t_token *token, char *tab_word,
		t_token redir, t_env **p_envlst)
{
	char	*cpy;

	token->file = ft_calloc(1, sizeof(t_file));
	if (!token->file)
		return (false);
	token->file->redir_type = get_redirection_type(redir.word[0]);
	if (token->file->redir_type == HEREDOC)
		cpy = remove_quotes(tab_word);
	else
		cpy = expand_file(tab_word, p_envlst);
	token->file->name = ft_strdup(cpy);
	free(cpy);
	if (!token->file->name)
		return (false);
	token->file->fd = 0;
	token->file->hdfd[0] = 0;
	token->file->hdfd[1] = 0;
	return (true);
}
