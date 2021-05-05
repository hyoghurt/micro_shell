#include "minishell.h"

void	check_token(void)
{
	char	**s;
	int		i;

	s = shell.cmd_table->token;
	i = 0;
	while (s[i])
	{
		printf("\e[1;38;5;10mtoken[%d]=\t[%s]\e[0m\n", i, s[i]);
		i++;
	}
	printf("\n");
}

void	check_status(void)
{
	printf("\e[1;38;5;10m\np shell.cmd_table=%p\e[0m\n", shell.cmd_table);
	printf("\e[1;38;5;10mstatus=[%d]\e[0m\n", shell.status);
	printf("\e[1;38;5;10mexit_executor\e[0m\n");
}

void	ft_executor(void)
{
	int	tmp_in;
	int	tmp_out;

	int	fd_in;
	int	fd_out;

	int	fd_pipe[2];

	t_cmd	*tmp_cmd;

	check_token();	//debager

	//save in/out
	tmp_in = dup(0);
	tmp_out = dup(1);

	//write error see for dup == -1

	tmp_cmd = shell.cmd_table;
	//initial input
	if (shell.in_file)
		fd_in = open(shell.in_file, O_RDONLY);
	else
		fd_in = dup(tmp_in);
	////////////////////////

	while (tmp_cmd)
	{
		//printf("ppp=%p\n", tm);
		//redirect input
		dup2(fd_in, 0);
		close(fd_in);
		///////////////////

		//setup output
		if (!tmp_cmd->next)		//last command
		{
			if (shell.out_file)
				fd_out = open(shell.out_file, O_CREAT);
			else
				fd_out = dup(tmp_out);
		}
		else	//no last command
		{
			pipe(fd_pipe);
			fd_out = fd_pipe[1];
			fd_in = fd_pipe[0];
		}
		//redirect output
		dup2(fd_out, 1);
		close(fd_out);

		//comand execve
		//create child process
		ft_create_child_process();

		//next command
		tmp_cmd = tmp_cmd->next;
	}

	//restore in/out default
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	close(tmp_in);
	close(tmp_out);

	check_status();
}

void	ft_create_child_process(void)
{
	shell.pathtkn = ft_path_token();
	if (!shell.pathtkn)
		printf("minishell: command not found: %s\n", shell.cmd_table->token[0]);
	else
	{
		ft_execve();
		free(shell.pathtkn);
		shell.pathtkn = 0;
	}
	ft_cmdclear(&shell.cmd_table);	//debager
}

void	ft_execve(void)
{
	pid_t	pid;
	pid_t	wpid;

	pid = fork();
	if (pid == 0)
	{
		//if (execve(str, shell.cmd_table->token, shell.set) == -1)
		execve(shell.pathtkn, shell.cmd_table->token, shell.set);
		printf("execve: %s\n", strerror(errno));
		exit(0);	// нужна чтоб остановить процесс, копия у дочернего
	}
	else if (pid < 0)	//error
		printf("fork: %s\n", strerror(errno));
	else	//wait exit child process
	{
		if (wait(&shell.status) == -1)
			ft_exit("error");
		//do 
		//{
		//	wpid = waitpid(pid, &shell.status, WUNTRACED);
		//} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
