/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:12:22 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:53:20 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_free(t_token *token);
static void	free_inside_cmd(t_token *token);
static void	free_inside_file(t_token *token);

void	tok_free(t_token ***token)
{
	int	index_up;
	int	index_deep;

	index_up = 0;
	index_deep = 0;
	if (!token || *token == NULL || **token == NULL)
		return ;
	while ((*token)[index_up])
	{
		while ((*token)[index_up][index_deep].type != END)
		{
			case_free(&(*token)[index_up][index_deep]);
			index_deep++;
		}
		if ((*token)[index_up][index_deep].type == END)
			case_free(&(*token)[index_up][index_deep]);
		free((*token)[index_up]);
		(*token)[index_up] = NULL;
		index_deep = 0;
		index_up++;
	}
	free(*token);
	*token = NULL;
}

static void	case_free(t_token *token)
{
	if (token->file != NULL)
		free_inside_file(token);
	if (token->cmd != NULL)
		free_inside_cmd(token);
	if (token->expanded != NULL)
	{
		free(token->expanded);
		token->expanded = NULL;
	}
	if (token->tool_str != NULL)
	{
		free(token->tool_str);
		token->tool_str = NULL;
	}
	if (token->word != NULL)
	{
		free_tab((void **)token->word, 0);
		token->word = NULL;
	}
}

static void	free_inside_file(t_token *token)
{
	if (token->file->name != NULL)
	{
		free(token->file->name);
		token->file->name = NULL;
	}
	free(token->file);
	token->file = NULL;
}

static void	free_inside_cmd(t_token *token)
{
	if (token->cmd->path_cmd != NULL)
	{
		free(token->cmd->path_cmd);
		token->cmd->path_cmd = NULL;
	}
	if (token->cmd->tab_cmd != NULL)
	{
		free_tab((void **)token->cmd->tab_cmd, 0);
		token->cmd->tab_cmd = NULL;
	}
	free(token->cmd);
	token->cmd = NULL;
}

void	clean_fd(void)
{
	int	index;

	index = 3;
	while (index < 1024)
	{
		close(index);
		index++;
	}
}
