#include "minishell.h"

int	ft_save_stdin_stdout(void)
{
	shell.std.tmp_in = dup(0);
	if (shell.std.tmp_in < 0)
		ft_exit("minishell: dup: ", "error");
	shell.std.tmp_out = dup(1);
	if (shell.std.tmp_out < 0)
	{
		close(shell.std.tmp_in);
		ft_exit("minishell: dup: ", "error");
	}
	return (0);
}

int	ft_fd_start(t_cmd *cmd)
{
	shell.std.fd_in = dup(shell.std.tmp_in);
	if (shell.std.fd_in < 0)
	{
		ft_restore_fd();
		ft_exit("minishell: dup: ", "error");
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
		ft_exit("minishell: dup: ", "error");
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

void	ft_restore_fd(void)
{
	int	ret;

	ret = dup2(shell.std.tmp_in, 0);
	close(shell.std.tmp_in);
	if (ret < 0)
	{
		close(shell.std.tmp_out);
		ft_exit("minishell: restore_fd_in dup2", "error");
	}
	ret = dup2(shell.std.tmp_out, 1);
	close(shell.std.tmp_out);
	if (ret < 0)
		ft_exit("minishell: restore_fd_out dup2", "error");
}
/*
int	ft_fd_end(t_cmd *cmd)
{
	shell.std.fd_out = dup(shell.std.tmp_out);
	if (shell.std.fd_out < 0)
	{
		ft_restore_fd();
		ft_exit("minishell: dup: ", "error");
	}
	return (0);
}

int	ft_redirect_input(void)
{
	dup2(shell.std.fd_in, 0);
	if (dup2(shell.std.fd_in, 0) < 0)
	{
		close(shell.std.fd_in);
		ft_restore_fd();
		ft_putstr_fd("minishell: redirect input: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(shell.std.fd_in);
	return (0);
}

int	ft_fd_start(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		shell.std.fd_in = cmd->fd_in;
	else
	{
		shell.std.fd_in = dup(shell.std.tmp_in);
		if (shell.std.fd_in < 0)
		{
			ft_restore_fd();
			ft_print_string("minishell", "dup", strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	ft_fd_end(t_cmd *cmd)
{
	if (cmd->fd_out != 1)
		shell.std.fd_out = cmd->fd_out;
	else
	{
		shell.std.fd_out = dup(shell.std.tmp_out);
		if (shell.std.fd_out < 0)
		{
			ft_restore_fd();
			ft_print_string("minishell", "dup", strerror(errno));
			return (1);
		}
	}
	return (0);
}
*/

