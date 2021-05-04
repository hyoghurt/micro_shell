#include "minishell.h"

void	ft_sigfunc(int sig)
{
	if (sig != SIGINT)
		write (1, "no_sig", 6);
	else
	{
		write (1, "[SIGINT]\n", 9);
	}
	exit (0);
}
