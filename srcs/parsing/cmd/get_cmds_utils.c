/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:40:36 by jbutte            #+#    #+#             */
/*   Updated: 2023/06/20 13:40:40 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	calculate_args(t_token *segment)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (segment[i].type != END)
	{
		if (segment[i].type == ARG || segment[i].type == COMMAND)
		{
			while (segment[i].word[j])
			{
				size++;
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (size);
}

char	*get_path(char **env)
{
	if (!env)
		return (NULL);
	while (*env && ft_strncmp("PATH=", *env, 5))
		env++;
	if (*env)
		return (*env + 5);
	else
		return (NULL);
}
