/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:23:48 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:14:19 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:29:07 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
<<<<<<< HEAD
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
=======
			return ((char*)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char*)s + i);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
	return (0);
}
