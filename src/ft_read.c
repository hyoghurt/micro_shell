#include "minishell.h"

void	ft_read_character(char *buf);

void	ft_read(void)
{
	char	buf[10];

	ft_init_termios();
	ft_set_prompt();
	while (1)
	{
		ft_memset(buf, 0, 10);
		if (read(0, buf, 10) < 0)
			ft_exit("minishell: read:", "error");
		if (buf[0] == '\n')
			break ;
		ft_read_character(buf);
	}
	g_shell.story->str = g_shell.line;
	tcsetattr(0, TCSANOW, &g_shell.termios_p);
	ft_putstr_fd("\n", 1);
}

void	ft_read_character(char *buf)
{
	ft_init_string(&g_shell.line);
	if (ft_strncmp(buf, g_shell.key.up, 3) == 0)
		ft_key_up();
	else if (ft_strncmp(buf, g_shell.key.down, 3) == 0)
		ft_key_down();
	else if (buf[0] == '\004' && ft_strlen(g_shell.line) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		ft_exit(0, 0);
	}
	else if (buf[0] == '\177')
		ft_key_backsp(g_shell.line);
	if ((buf[0] >= 32 && buf[0] <= 126) || (buf[0] >= 9 && buf[0] <= 13))
	{
		write (1, buf, 1);
		ft_strlcat(g_shell.line, buf, ft_strlen(g_shell.line) + 2);
	}
}
