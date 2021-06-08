/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:22:01 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:16:46 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/15 16:08:35 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
<<<<<<< HEAD
	if ((unsigned char *)dest <= (unsigned char *)src)
		ft_memcpy(dest, src, n);
	if ((unsigned char *)dest > (unsigned char *)src)
	{
		while (n)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
=======
	if ((unsigned char*)dest <= (unsigned char*)src)
		ft_memcpy(dest, src, n);
	if ((unsigned char*)dest > (unsigned char*)src)
	{
		while (n)
		{
			((unsigned char*)dest)[n - 1] = ((unsigned char*)src)[n - 1];
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
			n--;
		}
	}
	return (dest);
}
