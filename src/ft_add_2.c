#include "minishell.h"

size_t	ft_array_len(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_cpy_array_bi(char **s1, char **s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = ft_strdup(s2[i]);
		if (!s1[i])
		{
			ft_free_bi(s1);
			return (0);
		}
		i++;
	}
	s1[i] = 0;
	return (s1);
}

char	**ft_crt_arr_bi_from_list(t_list *list)
{
	size_t	size;
	char	**tokens;
	size_t	i;

	if (!list)
		return (0);
	size = ft_lstsize(list);
	tokens = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tokens)
		return (0);
	i = 0;
	while (i < size)
	{
		tokens[i] = ft_strdup(list->content);
		if (!tokens[i++])
		{
			ft_free_bi(tokens);
			return (0);
		}
		list = list->next;
	}
	tokens[i] = 0;
	return (tokens);
}
