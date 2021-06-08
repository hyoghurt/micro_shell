/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:36:58 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/06/08 07:26:43 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*m_zapolnenie(int n, int d, int j)
{
	int		i;
	char	*r;

	r = (char *)malloc(j + 1);
	if (!r)
		return (0);
	i = 0;
	if (n < 0)
	{
		r[i] = '-';
		j--;
		i++;
		n = n * (-1);
	}
	while (j--)
	{
		r[i] = n / d + '0';
		n = n % d;
		d = d / 10;
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		i;
	int		j;
	int		d;

	j = 1;
	d = 1;
	i = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		i = n * (-1);
		j = 2;
	}
	i = i / 10;
	while (i > 0)
	{
		j++;
		d = d * 10;
		i = i / 10;
	}
	r = m_zapolnenie(n, d, j);
	return (r);
}
