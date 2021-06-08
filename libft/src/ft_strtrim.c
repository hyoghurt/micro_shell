/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:37:29 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:09:20 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/15 16:01:22 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*r1;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	len = ft_strlen(s1);
	if (start == len)
	{
		r1 = ft_substr(s1, start, 0);
		return (r1);
	}
	while (ft_strchr(set, s1[len - 1]) && s1[len - 1])
		len--;
<<<<<<< HEAD
	r1 = ft_substr(s1, start, len - start);
	if (!r1)
=======
	if (!(r1 = ft_substr(s1, start, len - start)))
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	return (r1);
}
