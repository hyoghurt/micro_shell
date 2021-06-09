#include "minishell.h"

int		ft_echo(void)
{
	printf("in_echo\n");
	
	return (1);
}

int		ft_cd(void)
{
	printf("in_cd\n");
	return (1);
}

int		ft_pwd(void)
{
	printf("in_pwd\n");
	return (1);
}

int		ft_fn_selector(void)
{
	if (!ft_strncmp(shell.cmd_table->token[0], "echo", 5))
		return (ft_echo());
	if (!ft_strncmp(shell.cmd_table->token[0], "cd", 2))
		return (ft_cd());
	if (!ft_strncmp(shell.cmd_table->token[0], "pwd", 3))
		return (ft_pwd());
	return (0);
}
