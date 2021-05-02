#include "minishell.h"

void	ft_cache_bi(char *line)
{
	static size_t	i;
		
	if (line)
	{
		shell.cache_bi[i++] = line;
		shell.cache_bi[i] = 0;
	}
	write (1, "\n", 1);
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

char	*ft_read_character(char *buf, char *line_buf)
{
	char	*up;
	char	*backsp;

	up = tgetstr("up", 0);
	backsp = tgetstr("kb", 0);
	if (!up || !backsp)
		ft_exit ("error");
	if (ft_strncmp(buf, up, 2) == 0)
		return (ft_key_up(line_buf, up));
	else if (ft_strncmp(buf, backsp, 2) == 0)
		ft_key_backsp(line_buf);
	else if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
		write (1, buf, 1);
	return (ft_my_strjoin(line_buf, buf));
}

int		ft_check_lexer(char *line)
{
	//check lexer (example "echo fdsfd |") проверка нужно ли дописовать строку
	return (1);
}

char	*ft_read(void)
{
	char	buf[10];
	int		size_read;
	char	*line_buf;

	line_buf = 0;
	while (1)
	{
		ft_memset(buf, 0, 10);
		size_read = read(0, buf, 10);
		if (size_read < 0)
			ft_exit("error_read");
		if (buf[0] == '\n')
			if (ft_check_lexer(line_buf))
				break ;
		line_buf = ft_read_character(buf, line_buf);
		if (!line_buf)
			ft_exit("error");
	}
	ft_cache_bi(line_buf);
	return (line_buf);
}
