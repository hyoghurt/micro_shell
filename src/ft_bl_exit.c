#include "minishell.h"

int	ft_bl_exit(char **cmd)
{
	g_shell.exit = 0;
	//write value g_shell.exit

	ft_exit(0, 0);
	return (1);
}
