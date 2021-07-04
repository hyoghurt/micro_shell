#include "minishell.h"

void	ft_sig_ctrl_c(int sig)
{
	if (sig == SIGINT && !g_shell.pid)
	{
		tcsetattr(0, TCSANOW, &g_shell.termios_p);
		ft_putstr_fd("\n", 1);
		*g_shell.line = '\0';
		ft_init_termios();
		g_shell.fg_mv_story = 0;
		g_shell.move_story = g_shell.story;
		ft_set_prompt();
	}
	g_shell.status = 130;
}
