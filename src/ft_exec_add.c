#include "minishell.h"

void	ft_waitpid(void)
{
	t_pid	*my_p;

	my_p = shell.pid;
	while (my_p)
	{
		waitpid(my_p->pid, &shell.status, 0);
		my_p = my_p->next;
	}
	ft_pidclear(&shell.pid);
}

void	ft_killpid(void)
{
	t_pid	*my_p;

	my_p = shell.pid;
	while (my_p)
	{
		kill(my_p->pid, SIGINT);
		my_p = my_p->next;
	}
}

/*
int		ft_executor(void)
{
	t_cmd	*tmp_cmd;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	int		tmpin;
	int		tmpout;
	int		i;
	t_pid	*my_p;

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
		{
			my_p = shell.pid;
			while (my_p)
			{
				//printf("my_pid=%d\n", my_p->pid);
				kill(my_p->pid, SIGINT);
				my_p = my_p->next;
			}
			break ;
		}
		tmp_cmd = tmp_cmd->next;
	}
	//close(fdin);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	my_p = shell.pid;
	while (my_p)
	{
		//printf("pid=%d\n", shell.pid->pid);
		waitpid(my_p->pid, &shell.status, 0);
		my_p = my_p->next;
	}
	ft_pidclear(&shell.pid);

	return (0);
}
*/
