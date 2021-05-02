/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:34:06 by hyoghurt          #+#    #+#             */
/*   Updated: 2020/11/10 15:53:54 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	i = 0;
	if (!(r = (char *)malloc(len + 1)) || !s)
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
