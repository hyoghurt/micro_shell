#include "minishell.h"

static int	ft_check_pipe_error(void);
static int	ft_check_multiline(void);

int	ft_lexer(void)
{
	if (ft_check_pipe_error())
		return (1);
	if (ft_check_multiline())
		return (1);
	if (ft_check_lexer())
		return (1);
	return (0);
}

static int	ft_check_pipe_error(void)
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

static int	ft_check_multiline(void)
{
	char	*s;
	size_t	len;

	s = shell.line;
	len = ft_strlen(s);
	if (len)
	{
		if (s[len - 1] == '\\')
			return (1);
	}
	return (0);
}
