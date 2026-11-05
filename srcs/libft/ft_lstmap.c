/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutte <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:19:30 by jbutte            #+#    #+#             */
/*   Updated: 2022/10/22 15:45:44 by jbutte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*init;

	if (!lst || !f || !del)
		return (NULL);
	init = ft_lstnew(f(lst->content));
	if (!init)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
			ft_lstclear(&new, del);
		ft_lstadd_back(&init, new);
		lst = lst->next;
	}
	return (init);
}
