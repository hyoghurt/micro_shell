/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:24:39 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:07:28 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/10 14:24:40 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
<<<<<<< HEAD
	int	d;
=======
	int d;
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da

	result = 0;
	d = 1;
	i = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 8) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			d = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = (nptr[i] - '0') + result * 10;
		i++;
	}
	return (result * d);
}
