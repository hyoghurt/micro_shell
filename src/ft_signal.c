#include "minishell.h"

void		ft_sig_ctrl_c(int sig)
{
	if (shell.pid)
		return ;
	if (shell.fd_in != 0)
	{
		close(shell.fd_in);
		shell.fd_in = 0;
	}
	if (shell.fd_out != 1)
	{
		close(shell.fd_out);
		shell.fd_out = 1;
	}
	//shell.fg_mv_story = 0;						//flag for move story
	//shell.move_story = new;						//save pointer story for move
	//free(shell.line);
	//shell.line = ft_calloc(1, (BUF_SIZE * 2));
	//if (!shell.line)
	//	ft_exit("minishell: init_read: malloc:", "error");
	ft_putstr_fd("\n", 0);
	//ft_set_prompt();
}
