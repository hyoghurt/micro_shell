/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:36:58 by hyoghurt          #+#    #+#             */
/*   Updated: 2020/11/19 12:13:45 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	m_zapolnenie(char *r, int n, int d, int j)
{
	int	i;

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
}

char		*ft_itoa(int n)
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
	while ((i = i / 10) > 0)
	{
		j++;
		d = d * 10;
	}
	if (!(r = (char *)malloc(j + 1)))
		return (0);
	m_zapolnenie(r, n, d, j);
	return (r);
}
