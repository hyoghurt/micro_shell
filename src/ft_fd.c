#include "minishell.h"

int	ft_save_stdin_stdout(void)
{
	shell.std.tmp_in = dup(0);
	if (shell.std.tmp_in < 0)
		ft_exit("minishell: save_std: dup: ", "error");
	shell.std.tmp_out = dup(1);
	if (shell.std.tmp_out < 0)
	{
		close(shell.std.tmp_in);
		ft_exit("minishell: save_std: dup: ", "error");
	}
	return (0);
}

void	ft_restore_fd(void)
{
	int	ret;

	ret = dup2(shell.std.tmp_in, 0);
	close(shell.std.tmp_in);
	if (ret < 0)
	{
		close(shell.std.tmp_out);
		ft_exit("minishell: restore_fd: dup2: ", "error");
	}
	ret = dup2(shell.std.tmp_out, 1);
	close(shell.std.tmp_out);
	if (ret < 0)
		ft_exit("minishell: restore_fd: dup2: ", "error");
}
