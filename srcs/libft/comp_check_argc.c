/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_check_argc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:41:27 by jbutte            #+#    #+#             */
/*   Updated: 2023/02/26 19:46:10 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_minimum(int argc, int min)
{
	if (argc < min)
	{
		err_std("Not enough arguments");
		return (1);
	}
	return (0);
}

static int	check_maximum(int argc, int max)
{
	if (argc > max)
	{
		err_std("Too many arguments");
		return (1);
	}
	return (0);
}

int	check_argc(int argc, unsigned int min, unsigned int max)
{
	if (min == 0 && max == 0)
	{
		if (argc > 0)
			return (0);
	}
	else if (min == 0)
	{
		if (check_maximum(argc, max))
			return (1);
	}
	else if (max == 0)
	{
		if (check_minimum(argc, min))
			return (1);
	}
	else
	{
		if (check_minimum(argc, min) || check_maximum(argc, max))
			return (1);
	}
	return (0);
}
