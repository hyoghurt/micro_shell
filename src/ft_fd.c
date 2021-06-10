#include "minishell.h"

int			ft_save_stdin_stdout(void);
int			ft_fd_in(void);
int			ft_fd_out(void);
void		ft_fd_pipe(void);
int			ft_redirect_input(void);
int			ft_redirect_output(void);
void		ft_restore_fd(void);

int	ft_save_stdin_stdout(void)
{
	shell.std.tmp_in = dup(0);
	if (shell.std.tmp_in < 0)
	{
		ft_putstr_fd("minishell: save_stdin: dup: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	shell.std.tmp_out = dup(1);
	if (shell.std.tmp_out < 0)
	{
		close(shell.std.tmp_in);
		ft_putstr_fd("minishell: save_stdout: dup: ", 2);
		return (1);
	}
	return (0);
}

int	ft_fd_in(void)
{
	if (shell.std.fd_in_file != -1)
		shell.std.fd_in = shell.std.fd_in_file;
	else
	{
		shell.std.fd_in = dup(shell.std.tmp_in);
		if (shell.std.fd_in < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: dup:", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_fd_out(void)
{
	if (shell.std.fd_out_file != -1)
		shell.std.fd_out = shell.std.fd_out_file;
	else
	{
		shell.std.fd_out = dup(shell.std.tmp_out);
		if (shell.std.fd_out < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: dup:", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_redirect_input(void)
{
	if (dup2(shell.std.fd_in, 0) < 0)
	{
		close(shell.std.fd_in);
		ft_restore_fd();
		ft_putstr_fd("minishell: redirect input:", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(shell.std.fd_in);
	return (0);
}

int	ft_redirect_output(void)
{
	if (dup2(shell.std.fd_out, 1) < 0)
	{
		close(shell.std.fd_out);
		ft_restore_fd();
		ft_putstr_fd("minishell: redirect output:", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	close(shell.std.fd_out);
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
		ft_exit("restore_fd_in dup2", "error");
	ret = dup2(shell.std.tmp_out, 1);
	close(shell.std.tmp_out);
	if (ret < 0)
		ft_exit("restore_fd_out dup2", "error");
}
