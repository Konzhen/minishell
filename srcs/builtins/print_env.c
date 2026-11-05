/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <jimmy.mennock@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:54:33 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/19 12:46:54 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_env **envlst)
{
	t_env	*tmp;

	tmp = *envlst;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->variable, tmp->value);
		else if (tmp->print_env == true)
			printf("%s=", tmp->variable);
		tmp = tmp->next;
	}
}
