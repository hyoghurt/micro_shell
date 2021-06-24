#include "minishell.h"

static int	ft_check_pipe_error(void);
static int	ft_check_multiline(void);

int	ft_lexer(void)
{
	int	res;

	res = 0;
	if (ft_check_pipe_error())
		res = 1;
	else if (ft_check_multiline())
		res = 1;
	else if (ft_check_lexer())
		res = 1;
	if (res == 1)
		g_shell.status = 2;
	return (res);
}

static int	ft_check_pipe_error(void)
{
	char	*s;
	char	*tmp;

	s = g_shell.line;
	while (ft_strchr(" \t", *s))
		s++;
	if (*s == '|' || *s == ';')
		return (1);
	tmp = ft_strrchr(s, '|');
	if (tmp)
	{
		if (g_shell.line != tmp && *(tmp - 1) == '\\')
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

	s = g_shell.line;
	len = ft_strlen(s);
	if (len == 1 && s[0] == '\\')
		return (1);
	if (len > 1)
	{
		if (s[len - 1] == '\\' && s[len - 2] != '\\')
			return (1);
	}
	return (0);
}
