#include "minishell.h"

int	ft_fd_start(t_cmd *cmd)
{
	shell.std.fd_in = dup(shell.std.tmp_in);
	if (shell.std.fd_in < 0)
	{
		ft_restore_fd();
		ft_exit("minishell: fd_start: dup: ", "error");
	}
	return (0);
}

int	ft_fd_end(t_cmd *cmd)
{
	shell.std.fd_out = dup(shell.std.tmp_out);
	if (shell.std.fd_out < 0)
	{
		ft_restore_fd();
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		ft_exit("minishell: fd_end: dup: ", "error");
	}
	return (0);
}

int	ft_redirect(int	one, int two)
{
	dup2(one, two);
	close(one);
	return (0);
}

void	ft_fd_pipe(void)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	shell.std.fd_out = fd_pipe[1];
	shell.std.fd_in = fd_pipe[0];
}
