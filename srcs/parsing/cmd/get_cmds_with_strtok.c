/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_with_strtok.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:26:50 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 13:40:16 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_path_cmd(char **path, char const *word)
{
	char	tool_str[PATH_MAX];

	if (!word || !*word)
		return (NULL);
	if (ft_strchr(word, '/'))
		return (ft_strdup(word));
	while (*path)
	{
		ft_strlcpy(tool_str, *path, sizeof(tool_str));
		ft_strlcat(tool_str, "/", sizeof(tool_str));
		ft_strlcat(tool_str, word, sizeof(tool_str));
		if (is_executable_file(tool_str))
			return (ft_strdup(tool_str));
		path++;
	}
	return (NULL);
}

bool	is_directory(char const *path)
{
	struct stat	data;

	return (lstat(path, &data) != -1 && S_ISDIR(data.st_mode));
}

bool	is_executable_file(char const *path)
{
	return (access(path, X_OK | F_OK) == 0 && !is_directory(path));
}
