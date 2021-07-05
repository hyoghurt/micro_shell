#include "minishell.h"

void	ft_waitpid(void)
{
	t_pid	*my_p;
	int		status;

	my_p = g_shell.pid;
	while (my_p)
	{
		waitpid(my_p->pid, &status, 0);
		if (g_shell.status != 127)
			g_shell.status = ((status & 0xff00) >> 8);
		my_p = my_p->next;
	}
	ft_pidclear(&g_shell.pid);
}

void	ft_killpid(void)
{
	t_pid	*my_p;

	my_p = g_shell.pid;
	while (my_p)
	{
		kill(my_p->pid, SIGINT);
		my_p = my_p->next;
	}
}
