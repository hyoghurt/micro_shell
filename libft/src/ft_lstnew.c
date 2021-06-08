/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:41:44 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:19:02 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/12/13 16:17:00 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!content)
		return (0);
<<<<<<< HEAD
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
=======
	if (!(new = (t_list *)malloc(sizeof(t_list))))
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
}
