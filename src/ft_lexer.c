#include "minishell.h"

int	ft_check_pipe_error(void)
{
	char	*s;
	char	*tmp;

	s = shell.line;
	while (ft_strchr(" \t", *s))
		s++;
	if (*s == '|')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	tmp = ft_strrchr(s, '|');
	if (tmp)
	{
		tmp++;
		while (*tmp && ft_strchr(" \t", *tmp))
			tmp++;
		if (*tmp == '\0')
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_check_quote(void)
{
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
	if (ft_check_quote())
		return (1);
	if (ft_check_redirect())
		return (1);
	return (0);
}
