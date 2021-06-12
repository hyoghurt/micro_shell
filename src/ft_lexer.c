#include "minishell.h"

int	ft_check_pipe_error(void)
{
	char	*s;
	char	*tmp;

	s = shell.line;
	while (ft_strchr(" \t", *s))
		s++;
	if (*s == '|')
		return (1);
	tmp = ft_strrchr(s, '|');
	if (tmp)
	{
		if (*(tmp - 1) == '\\')
			return (0);
		tmp++;
		while (*tmp && ft_strchr(" \t", *tmp))
			tmp++;
		if (*tmp == '\0')
			return (1);
	}
	return (0);
}

int	ft_check_multiline(void)
{
	char	*s;
	size_t	len;

	len = ft_strlen(s);
	if (len)
	{
		if (s[len - 1] == '\\')
			return (1);
	}
	return (0);
}

void	ft_check_quote_a(char c, int *one, int *two, char c2)
{
	if (c == '\'' && !(*one) && !(*two) && c2 != '\\')
		*one = 1;
	else if (c == '\'' && *one && !(*two))
		*one = 0;
	else if (c == '\"' && !(*two) && !(*one) && c2 != '\\')
		*two = 1;
	else if (c == '\"' && *two && !(*one) && c2 != '\\')
		*two = 0;
}

int	ft_check_quote(void)
{
	char	*s;
	int		one;
	int		two;

	one = 0;
	two = 0;
	s = shell.line;
	if (*s == '\'')
		one = 1;
	else if (*s == '\"')
		two = 1;
	s++;
	while (*s)
	{
		ft_check_quote_a(*s, &one, &two, *(s - 1));
		s++;
	}
	if (one || two)
		return (1);
	return (0);
}

int	ft_check_redirect(void)
{
	return (0);
}

int		ft_lexer(void)
{
	if (ft_check_pipe_error())
		return (1);
	if (ft_check_multiline())
		return (1);
	if (ft_check_quote())
		return (1);
	if (ft_check_redirect())
		return (1);
	return (0);
}
