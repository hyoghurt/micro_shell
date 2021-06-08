/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:36:10 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:13:15 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:36:11 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			l;
	char			*r;
	unsigned int	i;

	if (!s || !f)
		return (0);
	l = ft_strlen(s);
<<<<<<< HEAD
	r = (char *)malloc(l + 1);
	if (!r)
=======
	if (!(r = (char *)malloc(l + 1)))
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	i = 0;
	while (i < l)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	r[i] = '\0';
	return (r);
}
