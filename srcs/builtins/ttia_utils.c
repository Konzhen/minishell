/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttia_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:29:39 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/20 14:23:04 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	len_for_array(t_token **segment, int index_up);

bool	clean_fill_array(char **array, t_tta_tool *tool,
		t_token **segment, int index_up)
{
	int	k;

	k = 0;
	while (segment[index_up][tool->i].word[k])
	{
		array[tool->j] = ft_strdup(segment[index_up][tool->i].word[k]);
		if (!array[tool->j])
		{
			free_tab((void **)array, 0);
			return (false);
		}
		tool->j++;
		k++;
	}
	return (true);
}

void	setup_ttia(t_tta_tool *tool, t_token **segment, int index_up)
{
	tool->len = len_for_array(segment, index_up);
	tool->i = 0;
	tool->j = 0;
}

static size_t	len_for_array(t_token **segment, int index_up)
{
	size_t	index;
	size_t	len;
	int		i;

	index = 0;
	len = 0;
	i = 0;
	while (segment[index_up][index].type != END)
	{
		if (segment[index_up][index].type != ERROR && \
			segment[index_up][index].type != TFILE \
			&& segment[index_up][index].type != REDIR)
		{
			while (segment[index_up][index].word[i])
			{
				len++;
				i++;
			}
		}
		i = 0;
		index++;
	}
	return (len);
}
