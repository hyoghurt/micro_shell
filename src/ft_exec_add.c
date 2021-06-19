#include "minishell.h"

void	ft_waitpid(void)
{
	t_pid	*my_p;

	my_p = g_shell.pid;
	while (my_p)
	{
		waitpid(my_p->pid, &g_shell.status, 0);
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
