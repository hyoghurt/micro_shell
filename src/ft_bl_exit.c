#include "minishell.h"

int	ft_bl_exit(char **cmd)
{
	g_shell.exit = 0;
	if (cmd[0] || cmd[1])
		ft_exit(0, 0);
	if (cmd[2])
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}
