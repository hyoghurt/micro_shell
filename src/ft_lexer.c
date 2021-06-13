#include "minishell.h"

int	ft_check_pipe_error(void)
{
	char	*s;
	char	*tmp;

	s = shell.line;
	while (ft_strchr(" \t", *s))
		s++;
	if (*s == '|' || *s == ';')
		return (1);
	tmp = ft_strrchr(s, '|');
	if (tmp)
	{
		if (shell.line != tmp && *(tmp - 1) == '\\')
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
/*
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
*/
int	ft_lexer_quote(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && *tmp != '\'')
		tmp++;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp == '\0')
		return (1);
	tmp++;
	*s = tmp;
	return (0);
}

int	ft_lexer_quote_2(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && *tmp != '\"')
	{
		tmp++;
		if (*tmp && *tmp == '\"' && tmp != shell.line && *(tmp - 1) == '\\')
			tmp++;
	}
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp == '\0')
		return (1);
	tmp++;
	*s = tmp;
	return (0);
}

int	ft_lexer_redirect(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	if (*tmp && *tmp == '>')
		tmp++;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp == '\0' || *tmp == '<' || *tmp == '>' || *tmp == '|' || *tmp == ';')
		return (1);
	tmp++;
	*s = tmp;
	return (0);
}

int	ft_lexer_next(char **s)
{
	char	*tmp;

	tmp = *s;
	tmp++;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp && *tmp == ';')
		return (1);
	*s = tmp;
	return (0);
}

int	ft_check_lexer(void)
{
	char	*s;

	s = shell.line;
	while (*s)
	{
		if (*s == '\\')
			s += 2;
		else if (*s == '\'' && ft_lexer_quote(&s))
			return (1);
		else if (*s == '\"' && ft_lexer_quote_2(&s))
			return (1);
		else if (*s == ';' && ft_lexer_next(&s))
			return (1);
		else if (*s == '<' || *s == '>')
		{
			if (ft_lexer_redirect(&s))
				return (1);
		}
		s++;
	}
	return (0);
}

int		ft_lexer(void)
{
	if (ft_check_pipe_error())
		return (1);
	if (ft_check_multiline())
		return (1);
	if (ft_check_lexer())
		return (1);
	return (0);
}
