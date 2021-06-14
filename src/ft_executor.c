#include "minishell.h"

int	ft_create_child_process(char **cmd);
int	ft_execve(char **cmd);

int		ft_executor(void)
{
	t_cmd	*cmd;
	int		flag;

	flag = 0;
	cmd = shell.cmd_table;
	ft_save_stdin_stdout();
	ft_fd_start(cmd);
	while (cmd)
	{
		if (find_redirect_file(cmd))
			flag = 1;
		if (cmd->fd_in != 0)
			ft_redirect(cmd->fd_in, shell.std.fd_in);
		ft_redirect(shell.std.fd_in, 0);
		if (!cmd->next)
			ft_fd_end(cmd);
		else								
			ft_fd_pipe();
		if (cmd->fd_out != 1)
			ft_redirect(cmd->fd_out, shell.std.fd_out);
		ft_redirect(shell.std.fd_out, 1);
		if (!flag)
		{
			if (ft_create_child_process(cmd->token))
			{
				ft_killpid();
				break ;
			}
		}
		flag = 0;
		cmd = cmd->next;
	}
	ft_restore_fd();
	ft_waitpid();
	return (0);
}

int		ft_create_child_process(char **cmd)
{
	if (!ft_fn_selector())
	{
		shell.pathtkn = ft_path_token(cmd);			//valitza posle shell.pathtkn
		if (!shell.pathtkn)
		{
			ft_print_string("minishell", "command not found", cmd[0]);
			return (1);
		}
		else
		{
			if (ft_execve(cmd))
				return (1);
			free(shell.pathtkn);
			shell.pathtkn = 0;
		}
		return (0);
	}
	return (0);
}

int	ft_execve(char **cmd)
{
	pid_t	pid;
	t_pid	*new;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid < 0)
		ft_print_string("minishell", "pid", strerror(errno));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(shell.pathtkn, cmd, shell.set) == -1)
			ft_print_string("minishell", "execve", strerror(errno));
		exit(1);
	}
	new = ft_pidnew(pid);
	ft_addpid_back(&shell.pid, new);
	/*
	int	status;
	status = 0;
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (WIFEXITED(status))
	{
		t_pid	*my_p;
		my_p = shell.pid;
		while (my_p)
		{
			//printf("my_pid=%d\n", my_p->pid);
			kill(my_p->pid, SIGINT);
			my_p = my_p->next;
		}
		return (1);
	}
	*/
	return (0);
}
