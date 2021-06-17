/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoghurt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:04:28 by hyoghurt          #+#    #+#             */
/*   Updated: 2021/06/02 18:29:01 by hyoghurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*my_ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(len + 1);
	if (!new)
		return (0);
	i = -1;
	j = -1;
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++j])
	{
		new[i] = s2[j];
		i++;
	}
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*my_create(char **stak)
{
	char	*new;
	char	*pak;
	char	*pak2;

	pak = ft_strchr(*stak, '\n');
	if (!pak)
	{
		new = ft_strdup(*stak);
		free(*stak);
		*stak = 0;
	}
	else
	{
		new = ft_substr(*stak, 0, pak - *stak);
		pak2 = ft_strdup(pak + 1);
		free(*stak);
		*stak = pak2;
	}
	return (new);
}

int	my_free(char *string)
{
	free(string);
	return (-1);
}

int	ft_gnl(int fd, char **line)
{
	char			*buf;
	static char		*stak;
	int				bytes;

	buf = (char *)malloc(10 + 1);
	if (fd < 0 || !line || !buf)
		return (-1);
	if (!stak)
	{
		stak = ft_strdup("");
		if (!stak)
			return (my_free(buf));
	}
	bytes = 1;
	while (bytes && !(ft_strchr(stak, '\n')) && stak)
	{
		ft_bzero(buf, 11);
		bytes = read(fd, buf, 10);
		if (bytes >= 0)
		{
			stak = my_ft_strjoin(stak, buf);
			if (!stak)
				return (my_free(buf));
		}
	}
	free(buf);
	*line = my_create(&stak);
	if (!(*line) || bytes < 0)
		return (my_free(stak));
	if (stak)
		return (1);
	return (0);
}
