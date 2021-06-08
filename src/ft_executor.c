#include "minishell.h"

static void	ft_create_child_process(t_cmd *tmp_cmd);
static void	ft_execve(t_cmd *cmd);
int			ft_fd_in(void);
int			ft_fd_out(void);
void		ft_fd_pipe(void);
void		ft_restore_fd(void);
int			ft_save_stdin_stdout(void);
int			ft_redirect_input(void);

int		ft_executor(void)
{
	t_cmd	*tmp_cmd;

	//debag_check_token();					//debager
	tmp_cmd = shell.cmd_table;				//tmp cmd_table
	if (ft_save_stdin_stdout())					//save fd (restore last executor)
		return (1);
	if (ft_fd_in())					//open file if have '<', for redirect fd_in
		return (1);
	while (tmp_cmd)
	{
		if (ft_redirect_input())			//redirect input
			return (1);
		if (!tmp_cmd->next)					//if last command need open file if have '>' fd_out
		{
			if (ft_fd_out())
				return (1);
		}
		else								
			ft_fd_pipe();
		dup2(shell.std.fd_out, 1);			//redirect output
		close(shell.std.fd_out);
		ft_create_child_process(tmp_cmd);	//execve
		tmp_cmd = tmp_cmd->next;			//next pipe
	}
	ft_restore_fd();						//restore in/out default
	//debag_check_status();					//debager
	return (0);
}

int		ft_save_stdin_stdout(void)
{
	shell.std.tmp_in = dup(0);					//save in
	if (shell.std.tmp_in < 0)
	{
		ft_putstr_fd("minishell: save_stdin: dup: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	shell.std.tmp_out = dup(1);					//save out
	if (shell.std.tmp_out < 0)
	{
		close(shell.std.tmp_in);
		ft_putstr_fd("minishell: save_stdout: dup: ", 2);
		return (1);
	}
	return (0);
}

int		ft_fd_in(void)
{
	if (shell.in_file)
	{
		shell.std.fd_in = open(shell.in_file, O_RDONLY);
		if (shell.std.fd_in < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell.in_file, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (1);
		}
	}
	else
	{
		shell.std.fd_in = dup(shell.std.tmp_in);
		if (shell.std.fd_in < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: dup:", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (1);
		}
	}
	return (0);
}
		
int		ft_fd_out(void)
{
	if (shell.out_file)
	{
		shell.std.fd_out = open(shell.out_file, O_CREAT);
		if (shell.std.fd_out < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(shell.out_file, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			return (1);
		}
	}
	else
	{
		shell.std.fd_out = dup(shell.std.tmp_out);
		if (shell.std.fd_out < 0)
		{
			ft_restore_fd();
			ft_putstr_fd("minishell: dup:", 2);
			ft_putstr_fd(strerror(errno), 2);
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
		return (1);
	}
	close(shell.std.fd_in);
	return (0);
}

void	ft_fd_pipe(void)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	shell.std.fd_out = fd_pipe[1];
	shell.std.fd_in = fd_pipe[0];
}

static void	ft_create_child_process(t_cmd *tmp_cmd)
{
	if (!ft_fn_selector())
	{
		shell.pathtkn = ft_path_token(tmp_cmd);			//valitza posle shell.pathtkn
		if (!shell.pathtkn)
		{
			wait(0);
			printf("minishell: command not found: %s\n", tmp_cmd->token[0]);
		}
		else
		{
			ft_execve(tmp_cmd);							//process start
			free(shell.pathtkn);
			shell.pathtkn = 0;
		}
	}
}

static void	ft_execve(t_cmd *cmd)
{
	pid_t	pid;
	pid_t	wpid;

	pid = fork();

	if (pid < 0)									//error fork
	{
		ft_putstr_fd("minishell: pid: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (pid == 0)										//process child
	{
		signal(SIGINT, SIG_DFL);				//signal Ctrl-C
		if (execve(shell.pathtkn, cmd->token, shell.set) == -1)
		{
			ft_putstr_fd(cmd->token[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		exit(1);										//stop process child
	}
	else												//waiting exit child process
	{
		if (wait(&shell.status) == -1)
		{
			ft_putstr_fd("minishell: wait: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
	}
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
