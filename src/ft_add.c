#include "minishell.h"

int	ft_set_prompt(void)
{
	ft_putstr_fd ("\033[1;48;5;58m", 1);
	if (shell.user)
		ft_putstr_fd (shell.user, 1);
	else
		ft_putstr_fd ("USER", 1);
	ft_putstr_fd (" > \033[0m", 1);
	tputs(shell.key.sc, 1, ft_putint);	//save cursor position (need for backspace and move story)
	return (0);
}

int		ft_putint(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_print_string(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s3, 2);
	ft_putstr_fd("\n", 2);
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
