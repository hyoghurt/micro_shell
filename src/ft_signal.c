#include "minishell.h"

void	ft_sigfunc(int sig)
{
	if (sig != SIGINT)
		write (1, "no_sig", 6);
	else
	{
		write (1, "[SIGINT]\n", 9);
		exit (0);
	}
	
	//check my proverka cache
	int	i;
	i = 0;
	while(shell.cmd_table->token[i])
	{
		printf("bi[%d]=%s\n", i, shell.cmd_table->token[i]);
		i++;
	}
	exit (0);
}
