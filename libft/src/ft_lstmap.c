/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:53:25 by hyoghurt          #+#    #+#             */
/*   Updated: 2020/11/15 15:53:31 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newline;
	t_list	*new;

	if (!lst)
		return (0);
	newline = ft_lstnew((*f)(lst->content));
	if (!newline)
		return (0);
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			ft_lstclear(&newline, del);
			return (0);
		}
		ft_lstadd_back(&newline, new);
		lst = lst->next;
	}
	return (newline);
}
