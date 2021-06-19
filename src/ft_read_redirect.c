#include "minishell.h"

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

void	ft_init_read_redir(char **line)
{
	*line = 0;
	ft_init_termios();
	ft_init_string(line);
	tputs(shell.key.sc, 1, ft_putint);
	ft_putstr_fd("\033[1;48;5;20m > \033[0m", 1);
}

char	*ft_read_redir(void)
{
	char	buf[10];
	char	*line;

	ft_init_read_redir(&line);
	while (1)
	{
		ft_memset(buf, 0, 10);
		if (read(0, buf, 10) < 0)
			ft_exit("minishell: read_redir:", "error");
		if (buf[0] == '\004' && ft_strlen(line) == 0)
		{
			free(line);
			line = 0;
			ft_putstr_fd("minishell: end string C-d", 1);
			break ;
		}
		else if (buf[0] == '\n')
			break ;
		ft_read_character_redir(buf, &line);
	}
	tcsetattr(0, TCSANOW, &shell.termios_p);
	ft_putstr_fd("\n", 1);
	return (line);
}

void	ft_redir_read(char *string)
{
	char	*s;

	shell.fd_in = open(REDIR_MY, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		s = ft_read_redir();
		if (!s)
			break ;
		else if (!ft_strncmp(string, s, ft_strlen(string) + 1))
		{
			free(s);
			break ;
		}
		else
		{
			ft_putstr_fd(s, shell.fd_in);
			ft_putstr_fd("\n", shell.fd_in);
			free(s);
		}
	}
	close(shell.fd_in);
	shell.fd_in = open(REDIR_MY, O_RDONLY, 0644);
}
