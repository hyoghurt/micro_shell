#include "minishell.h"

int	ft_echo(char **args)
{
	size_t	i;
	int		n;

	n = 1;
	i = 1;
	while (args[i] && !ft_strncmp(args[i], "-n", 3))
	{
		i++;
		n = 0;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	g_shell.status = 0;
	return (1);
}
