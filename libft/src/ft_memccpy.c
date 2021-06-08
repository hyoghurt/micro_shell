/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:21:41 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:18:29 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:21:42 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
<<<<<<< HEAD
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (&((unsigned char *)dest)[i + 1]);
=======
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		if (((unsigned char*)src)[i] == (unsigned char)c)
			return (&((unsigned char*)dest)[i + 1]);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		i++;
	}
	return (0);
}
