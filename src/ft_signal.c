#include "minishell.h"

void	ft_sig_ctrl_c(int sig)
{
	if (wait(0) == -1)
	{
		write (1, "\n", 1);
		ft_set_prompt();
	}
}
