#include "minishell.h"

int		ft_echo(void)
{
	printf("in_echo\n");
	return (1);
}

int		ft_fn_selector(void)
{
	if (!ft_strncmp(shell.cmd_table->token[0], "echo", 5))
		return (ft_echo());
	return (0);
}
