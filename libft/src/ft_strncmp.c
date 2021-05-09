/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:24:29 by hyoghurt          #+#    #+#             */
/*   Updated: 2020/11/10 14:24:31 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	result = 0;
	i = 0;
	while (i < n && result == 0 && (s1[i] || s2[i]))
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (result);
}
