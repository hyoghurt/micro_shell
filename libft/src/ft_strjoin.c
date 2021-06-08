/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:32:17 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/06/08 07:13:52 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	r = (char *)malloc(i + 1);
	if (!r)
		return (0);
	ft_strlcpy(r, s1, ft_strlen(s1) + 1);
	ft_strlcat(r, s2, i + 1);
	return (r);
}
