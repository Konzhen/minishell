/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmennock <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:18:53 by jmennock          #+#    #+#             */
/*   Updated: 2023/06/05 09:56:12 by jmennock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ajouter le exit code en global
*/
int	g_exit;

int	main(int argc, char **argv, char **env)
{
	char	*input;

	g_exit = 0;
	input = NULL;
	if (check_argc(argc, 1, 1))
		return (1);
	(void)argv;
	ft_read_input(input, env);
	return (g_exit);
}
