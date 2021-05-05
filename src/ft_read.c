#include "minishell.h"

void	ft_cache_bi(char *line)
{
	static size_t	i;
		
	if (line)
	{
		shell.cache_bi[i++] = line;
		shell.cache_bi[i] = 0;
	}
	//write (1, "\n", 1);
}

char	*ft_my_strjoin(char *s1, const char *s2)
{
	size_t	len;
	char	*res;

	if (!s1)
	{
		res = ft_strdup(s2);
		return (res);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char*)malloc(len + 1);
	if (!res)
		return (res);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	free(s1);
	return (res);
}

void	ft_init_shell_line(void)
{
	size_t	len;
	size_t	rest;
	size_t	whole;
	char	*tmp;

	if (shell.line)
	{
		len = ft_strlen(shell.line);
		rest = len % BUF_SIZE;
		whole = len / BUF_SIZE;
		if (whole >= 1 && rest == 2)
		{
			tmp = (char*)malloc((whole + 2) * BUF_SIZE);
			ft_strlcpy(tmp, shell.line, len + 1);
			free(shell.line);
			shell.line = tmp;
		}
	}
	else
		shell.line = ft_calloc(1, (BUF_SIZE * 2));
	if (!shell.line)
		ft_exit("error");
}

void	ft_read_character(char *buf)
{
	char	*up;
	char	*backsp;

	ft_init_shell_line();

	up = tgetstr("up", 0);
	backsp = tgetstr("kb", 0);
	if (!up || !backsp)
		ft_exit ("error");

	if (ft_strncmp(buf, up, 3) == 0)			//key up
		ft_key_up(shell.line, up);

	else if (buf[0] == '\004')					//key C-D
		ft_exit(0);

	else if (ft_strncmp(buf, backsp, 2) == 0)	//key backspace
		ft_key_backsp();

	if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	//if (ft_strlen(buf) <= 1);
	{
		write (1, buf, ft_strlen(buf));
		ft_strlcat(shell.line, buf, ft_strlen(shell.line) + 2);
	}
}

int		ft_check_lexer(char *line)
{
	//check lexer (example "echo fdsfd |") проверка нужно ли дописовать строку
	return (1);
}

void	ft_read(void)
{
	char	buf[10];
	int		size_read;

	shell.line = 0;
	while (1)
	{
		ft_memset(buf, 0, 10);

		size_read = read(0, buf, 10);
		if (size_read < 0)
			ft_exit("error_read");

		if (buf[0] == '\n')
			if (ft_check_lexer(shell.line))
				break ;

		ft_read_character(buf);
	}
	ft_cache_bi(shell.line);
}
