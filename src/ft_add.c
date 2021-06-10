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

t_cmd	*ft_cmdnew(char	**token)
{
	t_cmd	*new;

	if (!token)
		return (0);
	new = (t_cmd*)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->token = token;
	new->next = 0;
	return (new);
}
		
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (!tmp)
		*cmd = new;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**ft_crt_arr_bi_from_list(t_list *list)
{
	size_t	size;
	char	**tokens;
	size_t	i;

	size = ft_lstsize(list);
	tokens = (char**)malloc(sizeof(char*) * (size + 1));
	if (!tokens)
		return (0);
	i = 0;
	while (i < size)
	{
		tokens[i] = ft_strdup(list->content);
		if (!tokens[i])
		{
			ft_free_bi(tokens);
			return (0);
		}
		list = list->next;
		i++;
	}
	tokens[i] = 0;
	return (tokens);
}

char	*ft_getset(char *str)
{
	char	**tmp;
	size_t	len;
	int		i;

	i = -1;
	if (!str)
		return (0);
	tmp = shell.set;
	len = ft_strlen(str);
	while (tmp[++i])
	{
		if (ft_strncmp(tmp[i], str, len) == 0)
		{
			if (*(tmp[i] + len) == '=')
				return (ft_strdup(tmp[i] + len + 1));
		}
	}
	return (0);
}
