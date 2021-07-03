#include "minishell.h"

int	ft_env_input_is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
	{
		if (i == 0)
		{
			if (s[i] != '_' && !ft_isalpha(s[i]))
			{
				g_shell.status = 1;
				return (0);
			}
		}
		else
		{
			if (s[i] != '_' && !ft_isalnum(s[i]))
			{
				g_shell.status = 1;
				return (0);
			}
		}
		if (s[i] == 0)
		return (0);
		i++;
	}
	return (1);
}

int	ft_env(void)
{
	char	**env;
	int		i;

	i = 0;
	env = g_shell.set;
	while (ft_env_input_is_valid(env[i]))
	{
		ft_putstr_fd(env[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	g_shell.status = 0;
	return (1);
}
