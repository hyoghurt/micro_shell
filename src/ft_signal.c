#include "minishell.h"

void		ft_sig_ctrl_c(int sig)
{
	if (!shell.pid)
	{
		tcsetattr(0, TCSANOW, &shell.termios_p);
		ft_putstr_fd("\n", 1);
		*shell.line = '\0';
		ft_init_termios();
		shell.fg_mv_story = 0;
		shell.move_story = shell.story;
		ft_set_prompt();
	}
}
