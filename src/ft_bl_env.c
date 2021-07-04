#include "minishell.h"

int	ft_env(void)
{
	char	**env;
	int		i;

	i = 0;
	env = g_shell.set;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	g_shell.status = 0;
	return (1);
}
