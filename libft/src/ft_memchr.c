/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:22:12 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:18:03 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:22:13 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
<<<<<<< HEAD
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((unsigned char *)s)[i]);
=======
		if (((unsigned char*)s)[i] == (unsigned char)c)
			return (&((unsigned char*)s)[i]);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		i++;
	}
	return (0);
}
