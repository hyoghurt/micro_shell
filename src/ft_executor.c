#include "minishell.h"

int	ft_run_cmd(t_cmd *cmd);
int	find_redirect_file(t_cmd *cmd);
int	ft_create_child_process(char **cmd);
int	ft_execve(char **cmd);

int	ft_executor(void)
{
	t_cmd	*cmd;

	cmd = g_shell.cmd_table;
	ft_save_stdin_stdout();
	ft_fd_start();
	while (cmd)
	{
		ft_run_cmd(cmd);
		if (cmd->next)
			g_shell.status = 0;
		cmd = cmd->next;
	}
	ft_restore_fd();
	ft_waitpid();
	return (0);
}

int	ft_run_cmd(t_cmd *cmd)
{
	int	flag;

	flag = 0;
	if (find_redirect_file(cmd))
		flag = 1;
	if (cmd->fd_in != 0)
		ft_redirect(cmd->fd_in, g_shell.std.fd_in);
	ft_redirect(g_shell.std.fd_in, 0);
	if (!cmd->next)
		ft_fd_end(cmd);
	else
		ft_fd_pipe();
	if (cmd->fd_out != 1)
		ft_redirect(cmd->fd_out, g_shell.std.fd_out);
	ft_redirect(g_shell.std.fd_out, 1);
	if (!flag)
		ft_create_child_process(cmd->token);
	return (0);
}

int	ft_create_child_process(char **cmd)
{
	if (!cmd)
		return (0);
	if (!ft_builting(cmd))
	{
		g_shell.pathtkn = ft_path_token(cmd);
		if (!g_shell.pathtkn)
		{
			ft_print_string("minishell", "command not found", cmd[0]);
			g_shell.status = 127;
			return (1);
		}
		ft_execve(cmd);
		free(g_shell.pathtkn);
		g_shell.pathtkn = 0;
	}
	return (0);
}

int	ft_execve(char **cmd)
{
	pid_t	pid;
	t_pid	*new;

	pid = fork();
	if (pid < 0)
		ft_print_string("minishell", "pid", strerror(errno));
	if (pid == 0)
	{
		if (execve(g_shell.pathtkn, cmd, g_shell.set) == -1)
			ft_print_string("minishell", "execve", strerror(errno));
		exit(1);
	}
	new = ft_pidnew(pid);
	ft_addpid_back(&g_shell.pid, new);
	return (0);
}

int	find_redirect_file(t_cmd *cmd)
{
	if (cmd->fd_in < 0)
	{
		ft_print_string("minishell", cmd->fd_in_file, strerror(errno));
		g_shell.status = 1;
		return (1);
	}
	if (cmd->fd_out < 0)
	{
		ft_print_string("minishell", cmd->fd_out_file, strerror(errno));
		g_shell.status = 1;
		return (1);
	}
	return (0);
}
