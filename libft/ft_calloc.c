/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:27:39 by hyoghurt          #+#    #+#             */
/*   Updated: 2020/11/15 16:21:47 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*i;

	if (!(i = (void *)malloc(nmemb * size)))
		return (0);
	ft_bzero(i, nmemb * size);
	return (i);
}
