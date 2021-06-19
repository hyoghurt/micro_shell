#include "minishell.h"

int	ft_putint(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_print_string(char *s1, char *s2, char *s3)
{
	if (s1)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s3)
		ft_putstr_fd(s3, 2);
	ft_putstr_fd("\n", 2);
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

char	*ft_value_getset(void)
{
	char	*start;
	char	*tmp;
	char	*content;

	start = shell.line;
	while (ft_isalnum(*shell.line) || *shell.line == '_')
		shell.line++;
	tmp = ft_substr(start, 0, shell.line - start);
	if (!tmp)
		return (0);
	content = ft_getset(tmp);
	free(tmp);
	return (content);
}

void	ft_init_string(char **s)
{
	size_t	len;
	size_t	rest;
	size_t	whole;
	char	*tmp;

	if (*s)
	{
		len = ft_strlen(*s);
		rest = len % BUF_SIZE;
		whole = len / BUF_SIZE;
		if (whole >= 1 && rest == 2)
		{
			tmp = (char *)malloc((whole + 2) * BUF_SIZE);
			ft_strlcpy(tmp, *s, len + 1);
			free(*s);
			*s = tmp;
		}
	}
	else
		*s = ft_calloc(1, (BUF_SIZE * 2));
	if (!(*s))
		ft_exit("minishell: init_shell_line: malloc: ", "error");
}
