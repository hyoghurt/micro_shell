#include "minishell.h"

int		ft_echo(void)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!ft_strncmp(shell.cmd_table->token[1], "-n", 1))
	{
		i = 2;
		j = 1;
	}
	while (shell.cmd_table->token[i] != 0)
	{
		ft_putstr_fd(shell.cmd_table->token[i],1);
		if (shell.cmd_table->token[i+1] != 0)
		{
			ft_putstr_fd(" ", 1);
		}
		i++;
	}
	(j == 1) ? printf("%%"):0;
	printf("\n");
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
