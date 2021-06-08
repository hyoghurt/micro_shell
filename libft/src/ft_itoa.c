/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:36:58 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:26:43 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/19 12:13:45 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD
static char	*m_zapolnenie(int n, int d, int j)
{
	int		i;
	char	*r;

	r = (char *)malloc(j + 1);
	if (!r)
		return (0);
=======
static void	m_zapolnenie(char *r, int n, int d, int j)
{
	int	i;

>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
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
<<<<<<< HEAD
	return (r);
}

char	*ft_itoa(int n)
=======
}

char		*ft_itoa(int n)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
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
<<<<<<< HEAD
	i = i / 10;
	while (i > 0)
	{
		j++;
		d = d * 10;
		i = i / 10;
	}
	r = m_zapolnenie(n, d, j);
=======
	while ((i = i / 10) > 0)
	{
		j++;
		d = d * 10;
	}
	if (!(r = (char *)malloc(j + 1)))
		return (0);
	m_zapolnenie(r, n, d, j);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
	return (r);
}
