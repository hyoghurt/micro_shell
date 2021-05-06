#include "minishell.h"

void	check_token(void)
{
	char	**s;
	t_cmd	*tmp;
	int		i;

	tmp = shell.cmd_table;
	while (tmp)
	{
		s = tmp->token;
		i = 0;
		while (s[i])
		{
			printf("\e[1;38;5;10mtoken[%d]=\t[%s]\e[0m\n", i, s[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
}

void	check_status(void)
{
	printf("\e[1;38;5;10m\np shell.cmd_table=%p\e[0m\n", shell.cmd_table);
	printf("\e[1;38;5;10mstatus=[%d]\e[0m\n", shell.status);
	printf("\e[1;38;5;10mexit_executor\e[0m\n");
}

typedef struct	s_fd
{
	int			tmp_in;
	int			tmp_out;
	int			fd_in;
	int			fd_out;
	int			fd_pipe[2];
}				t_fd;

static void	ft_create_child_process(t_cmd *tmp_cmd);
static void	ft_execve(t_cmd *cmd);
int			ft_fd_in(t_fd *std);
int			ft_fd_out(t_fd *std);
void		ft_fd_pipe(t_fd *std);
void		ft_restore_fd(t_fd *std);

//write error see for dup == -1
void	ft_executor(void)
{
	t_fd	std;
	t_cmd	*tmp_cmd;

	check_token();				//debager
	tmp_cmd = shell.cmd_table;	//tmp cmd_table
	std.tmp_in = dup(0);		//save in
	std.tmp_out = dup(1);		//save out
	std.fd_in = ft_fd_in(&std);	//initial input
	while (tmp_cmd)
	{
		dup2(std.fd_in, 0);		//redirect input
		close(std.fd_in);

		if (!tmp_cmd->next)		//last command fd_out
			std.fd_out = ft_fd_out(&std);
		else					//no last command
			ft_fd_pipe(&std);

		dup2(std.fd_out, 1);	//redirect output
		close(std.fd_out);

		ft_create_child_process(tmp_cmd);	//execve
		tmp_cmd = tmp_cmd->next;			//next pipe
	}
	ft_restore_fd(&std);		//restore in/out default
	ft_cmdclear(&shell.cmd_table);			//inside (shell.cmd_table = 0)
	//write func free shell.fd_in and out
	check_status();				//debager
}

static void	ft_create_child_process(t_cmd *tmp_cmd)
{
	shell.pathtkn = ft_path_token(tmp_cmd);			//valitza posle shell.pathtkn
	if (!shell.pathtkn)
		printf("minishell: command not found: %s\n", tmp_cmd->token[0]);
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
	if (pid == 0)										//process child
	{
		execve(shell.pathtkn, cmd->token, shell.set);
		printf("execve: %s\n", strerror(errno));		//write stderr
		exit(1);										//stop process child
	}
	else if (pid < 0)									//error fork
		printf("fork: %s\n", strerror(errno));			//write stderr
	else												//waiting exit child process
	{
		if (wait(&shell.status) == -1)
			ft_exit("error");
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

void	ft_fd_pipe(t_fd *std)
{
	pipe(std->fd_pipe);
	std->fd_out = std->fd_pipe[1];
	std->fd_in = std->fd_pipe[0];
}

void	ft_restore_fd(t_fd *std)
{
	dup2(std->tmp_in, 0);
	dup2(std->tmp_out, 1);

	close(std->tmp_in);
	close(std->tmp_out);
}
