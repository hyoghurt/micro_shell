/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:37:29 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/06/08 07:09:20 by hyoghurt         ###   ########.fr       */
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
	r1 = ft_substr(s1, start, len - start);
	if (!r1)
		return (0);
	return (r1);
}
