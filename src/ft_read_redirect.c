#include "minishell.h"

char	*ft_read_redir(char *string);
void	ft_init_read_redir(char **line);
int		ft_rtn_str_read_ch(char **line);
void	ft_read_character_redir(char *buf, char **line);

void	ft_redir_content(char *string)
{
	char	*s;

	g_shell.fd_in = open(REDIR_MY, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = ft_read_redir(string);
		if (!s)
			break ;
		else
		{
			ft_putstr_fd(s, g_shell.fd_in);
			ft_putstr_fd("\n", g_shell.fd_in);
			free(s);
		}
	}
	close(g_shell.fd_in);
	g_shell.fd_in = open(REDIR_MY, O_RDONLY, 0644);
}

char	*ft_read_redir(char *string)
{
	char	*line;

	ft_init_read_redir(&line);
	while (1)
	{
		if (ft_rtn_str_read_ch(&line))
			break ;
	}
	if (line)
	{
		if (!ft_strncmp(string, line, ft_strlen(string) + 1))
		{
			free(line);
			line = 0;
		}
		else
			line = ft_string_check_env(line);
	}
	tcsetattr(0, TCSANOW, &g_shell.termios_p);
	ft_putstr_fd("\n", 1);
	return (line);
}

void	ft_init_read_redir(char **line)
{
	*line = 0;
	ft_init_termios();
	ft_init_string(line);
	ft_putstr_fd("\033[1;48;5;20m > \033[0m", 1);
	tputs(g_shell.key.sc, 1, ft_putint);
}

int	ft_rtn_str_read_ch(char **line)
{
	char	buf[10];

	ft_memset(buf, 0, 10);
	if (read(0, buf, 10) < 0)
		ft_exit("minishell: read_redir:", "error");
	if (buf[0] == '\004' && ft_strlen(*line) == 0)
	{
		ft_putstr_fd("minishell: end string C-d", 1);
		free(*line);
		*line = 0;
		return (1);
	}
	else if (buf[0] == '\n')
		return (1);
	ft_read_character_redir(buf, line);
	return (0);
}

void	ft_read_character_redir(char *buf, char **line)
{
	ft_init_string(line);
	if (buf[0] == '\177')
		ft_key_backsp(*line);
	else if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	{
		write (1, buf, 1);
		ft_strlcat(*line, buf, ft_strlen(*line) + 2);
	}
}
