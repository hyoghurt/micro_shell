#include "minishell.h"

int	ft_set_prompt(void)
{
	char	*user;

	//user = getenv("USER");
	user = "USER";
	write (1, "\033[1;48;5;58m", strlen("\033[1;48;5;58m"));
	if (user)
		write (1, user, strlen(user));
	write (1, " > ", 3);
	write (1, "\033[0m", strlen("\033[0m"));
	return (0);
}

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

int		ft_putint(int c)
{
	write(1, &c, 1);
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
	if (!(*cmd))
		*cmd = new;
	else
	{
		while((*cmd)->next)
			*cmd = (*cmd)->next;
		(*cmd)->next = new;
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

	tmp = shell.set;
	len = ft_strlen(str);
	while (*tmp)
	{
		if (ft_strncmp(*tmp, str, len) == 0)
		{
			if (*(*tmp + len) == '=')
				return (ft_strdup(*tmp + len + 1));
		}
		*tmp++;
	}
	return (0);
}
