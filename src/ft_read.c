#include "minishell.h"

void	ft_read_character(char *buf);

void	ft_read(void)
{
	char	buf[10];

	while (1)
	{
		ft_memset(buf, 0, 10);
		if (read(0, buf, 10) < 0)
			ft_exit("minishell: read:", "error");
		if (buf[0] == '\n')
			break ;
		ft_read_character(buf);
	}
	shell.story->str = shell.line;
	tcsetattr(0, TCSANOW, &shell.termios_p);
	ft_putstr_fd("\n", 1);
}

void	ft_read_character(char *buf)
{
	ft_init_shell_line();	//realoc if it's necessary for shell.line
	if (ft_strncmp(buf, shell.key.up, 3) == 0)
		ft_key_up();
	else if (ft_strncmp(buf, shell.key.down, 3) == 0)
		ft_key_down();
	else if (buf[0] == '\004' && ft_strlen(shell.line) == 0)
		ft_exit(0, 0);
	else if (buf[0] == '\177')
		ft_key_backsp();
	if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	{
		write (1, buf, 1);
		ft_strlcat(shell.line, buf, ft_strlen(shell.line) + 2);
	}
}
