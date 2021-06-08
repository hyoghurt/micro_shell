#include "minishell.h"

static void	ft_create_child_process(t_cmd *tmp_cmd);
static void	ft_execve(t_cmd *cmd);
int			ft_fd_in(t_fd *std);
int			ft_fd_out(t_fd *std);
void		ft_fd_pipe(t_fd *std);
void		ft_restore_fd(void);

//write error see for dup == -1
int		ft_save_in_out(void)
{
	shell.std.tmp_in = dup(0);					//save in
	if (shell.std.tmp_in < 0)
	{
<<<<<<< HEAD
		ft_putstr_fd("minishell: save_stdin: dup: ", 2);
=======
		ft_putstr_fd("save_stdin: dup: ", 2);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	shell.std.tmp_out = dup(1);					//save out
	if (shell.std.tmp_out < 0)
	{
		close(shell.std.tmp_in);
<<<<<<< HEAD
		ft_putstr_fd("minishell: save_stdin: dup: ", 2);
=======
		ft_putstr_fd("save_stdin: dup: ", 2);
>>>>>>> c8528fe1c906ed3fcf64355d5c43dea9fff470da
		return (1);
	}
	return (0);
}

int		ft_init_input(void)
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
		shell.std.fd_in = dup(shell.std.tmp_in);
	if (shell.std.fd_in < 0)
	{
		ft_restore_fd();
		ft_putstr_fd("minishell: dup:", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
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

void	ft_fd_pipe(t_fd *std)
{
	pipe(std->fd_pipe);
	std->fd_out = std->fd_pipe[1];
	std->fd_in = std->fd_pipe[0];
}

int		ft_executor(void)
{
	t_cmd	*tmp_cmd;

	//debag_check_token();					//debager
	tmp_cmd = shell.cmd_table;				//tmp cmd_table
	if (ft_save_in_out())
		return (1);
	if (ft_init_input())
		return (1);
	while (tmp_cmd)
	{
		if (ft_redirect_input())			//redirect input
			return (1);
		if (!tmp_cmd->next)					//last command fd_out
			shell.std.fd_out = ft_fd_out(&shell.std);
		else								//no last command
			ft_fd_pipe(&shell.std);
		dup2(shell.std.fd_out, 1);			//redirect output
		close(shell.std.fd_out);
		ft_create_child_process(tmp_cmd);	//execve
		tmp_cmd = tmp_cmd->next;			//next pipe
	}
	ft_restore_fd();						//restore in/out default
	//debag_check_status();					//debager
	return (0);
}

static void	ft_create_child_process(t_cmd *tmp_cmd)
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

int		ft_fd_in(t_fd *std)
{
	int	fd_in;

	if (shell.in_file)
		fd_in = open(shell.in_file, O_RDONLY);
	else
		fd_in = dup(std->tmp_in);
	return (fd_in);
}

int		ft_fd_out(t_fd *std)
{
	int	fd_out;

	if (shell.out_file)
		fd_out = open(shell.out_file, O_CREAT);
	else
		fd_out = dup(std->tmp_out);
	return (fd_out);
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
