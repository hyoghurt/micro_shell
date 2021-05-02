/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:01:33 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/02/10 22:14:53 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*bg;

	while (*lst)
	{
		bg = *lst;
		*lst = (*lst)->next;
		del(bg->content);
		free(bg);
	}
}
