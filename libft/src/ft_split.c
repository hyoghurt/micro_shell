/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:37:22 by hyoghurt          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/08 07:16:04 by hyoghurt         ###   ########.fr       */
=======
/*   Updated: 2020/11/19 12:17:22 by hyoghurt         ###   ########.fr       */
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	m_count(char const *s, char c)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	if (s[i] != c && s[i])
		k++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			k++;
		i++;
	}
	return (k);
}

static size_t	m_lench(char const *s, size_t i, char c)
{
	size_t	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

<<<<<<< HEAD
static void	m_clear(char **r, size_t j)
=======
static void		m_clear(char **r, size_t j)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(r[i]);
		i++;
	}
	free(r);
	r = 0;
}

<<<<<<< HEAD
static void	m_zapolnen(char **r, char const *s, char c, size_t k)
=======
static void		m_zapolnen(char **r, char const *s, char c, size_t k)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s) && j < k && r)
	{
		if (s[i] != c)
		{
			r[j] = ft_substr(s, i, m_lench(s, i, c));
			if (!r[j])
				m_clear(r, j);
			j++;
			i = i + m_lench(s, i, c);
		}
		i++;
	}
	if (r)
		r[j] = 0;
}

<<<<<<< HEAD
char	**ft_split(char const *s, char c)
=======
char			**ft_split(char const *s, char c)
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
{
	size_t	k;
	char	**r;

	if (!s)
		return (0);
	k = m_count(s, c);
<<<<<<< HEAD
	r = (char **)malloc(sizeof(char *) * (k + 1));
	if (!r)
=======
	if (!(r = (char **)malloc(sizeof(char *) * (k + 1))))
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (0);
	m_zapolnen(r, s, c, k);
	return (r);
}
