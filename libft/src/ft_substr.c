/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:34:06 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:08:29 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 15:53:54 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	i = 0;
<<<<<<< HEAD
	r = (char *)malloc(len + 1);
	if (!r || !s)
=======
	if (!(r = (char *)malloc(len + 1)) || !s)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	if (ft_strlen(s) > start)
	{
		while (len > i)
		{
			r[i] = s[start + i];
			i++;
		}
	}
	r[i] = '\0';
	return (r);
}
