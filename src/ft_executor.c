#include "minishell.h"

int	ft_create_child_process(char **cmd);
static void	ft_execve(char **cmd);

int	find_redirect_file(char **token)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (token[i])
	{
		if (!ft_strncmp(token[i], "<", 2))
		{
			if (shell.std.fd_in_file != -1)
				close(shell.std.fd_in_file);
			shell.std.fd_in_file = open(token[i + 1], O_RDONLY);
			if (shell.std.fd_in_file < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(token[i + 1], 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			i += 2;
			free(token[i]);
			free(token[i + 1]);
		}
		else
		{
			token[j] = token[i];
			j++;
			i++;
		}
	}
	token[j] = 0;
	return (0);
}

int		ft_executor(void)
{
	t_cmd	*tmp_cmd;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		tmpin;
	int		tmpout;
	int		i;

	tmp_cmd = shell.cmd_table;				//tmp cmd_table

	tmpin = dup(0);
	tmpout = dup(1);

	fdin = dup(tmpin);

	while (tmp_cmd)
	{
		dup2(fdin, 0);
		close(fdin);

		if (!tmp_cmd->next)
			fdout = dup(tmpout);
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		if (ft_create_child_process(tmp_cmd->token))
			break ;
		tmp_cmd = tmp_cmd->next;
	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	//kill(shell.pid->pid, SIGINT);

	while (shell.pid)
	{
		//printf("pid=%d\n", shell.pid->pid);
		waitpid(shell.pid->pid, &shell.status, 0);
		shell.pid = shell.pid->next;
	}

	return (0);
}

/*
int		ft_executor(void)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = shell.cmd_table;				//tmp cmd_table

	if (ft_save_stdin_stdout())					//save fd (restore last executor)
		return (1);
	if (ft_fd_in())					//open file if have '<', for redirect fd_in
		return (1);
	while (tmp_cmd)
	{
		if (!find_redirect_file(tmp_cmd->token))
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
			if (ft_redirect_output())			//redirect output
				return (1);
			ft_create_child_process(tmp_cmd->token);	//execve
		}
		tmp_cmd = tmp_cmd->next;			//next pipe
	}
	ft_restore_fd();						//restore in/out default
	return (0);
}
*/

int		ft_create_child_process(char **cmd)
{
	//if (!ft_fn_selector())
	//{
		shell.pathtkn = ft_path_token(cmd);			//valitza posle shell.pathtkn
		if (!shell.pathtkn)
		{
			//wait(0);
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd("\n", 2);
			shell.pid = 0;
			kill(0, SIGINT);
			
			return (1);
		}
		else
		{
			ft_execve(cmd);
			free(shell.pathtkn);
			shell.pathtkn = 0;
		}
		return (0);
	//}
}

t_pid	*ft_pidnew(int n)
{
	t_pid	*new;

	new = (t_pid*)malloc(sizeof(t_pid));
	if (!new)
		return (0);
	new->pid = n;
	new->next = 0;
	return (new);
}

void	ft_addpid_back(t_pid **pid, t_pid *new)
{
	t_pid	*tmp;

	tmp = *pid;
	if (!tmp)
		*pid = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	ft_execve(char **cmd)
{
	pid_t	pid;
	t_pid	*new;

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
		if (execve(shell.pathtkn, cmd, shell.set) == -1)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		exit(1);										//stop process child
	}
	new = ft_pidnew(pid);
	ft_addpid_back(&shell.pid, new);
}
