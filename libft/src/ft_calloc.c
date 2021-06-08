/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:27:39 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:33:32 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/15 16:21:47 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*i;

<<<<<<< HEAD
	i = (void *)malloc(nmemb * size);
	if (!i)
=======
	if (!(i = (void *)malloc(nmemb * size)))
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	ft_bzero(i, nmemb * size);
	return (i);
}
