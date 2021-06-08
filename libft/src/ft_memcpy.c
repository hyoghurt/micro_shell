/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:21:29 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:17:16 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:21:31 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

<<<<<<< HEAD
	if (!(unsigned char *)dest && !(unsigned char *)src)
=======
	if (!(unsigned char*)dest && !(unsigned char*)src)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (dest);
	i = 0;
	while (i < n)
	{
<<<<<<< HEAD
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
=======
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		i++;
	}
	return (dest);
}
