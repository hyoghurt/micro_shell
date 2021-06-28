#include "minishell.h"

int	ft_var_is_present(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (g_shell.set[i])
	{
		j = 0;
		while (g_shell.set[i][j] == s[j])
		{
			if (g_shell.set[i][j] == '=')
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void	ft_swap_var_val(int i, char *s)
{
	char	*var;

	free(g_shell.set[i]);
	var = ft_strdup(s);
	if (var == 0)
		ft_exit(0, 0);
	g_shell.set[i] = var;
}

void	ft_print_declare(char *s)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (s[i] != '=')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, &s[i], 1);
	write(1, "\"", 1);
	i++;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

int	ft_export(char **cmd)
{
	int		n;
	int		i;
	int		j;
	char	**env_var;

	n = ft_array_len(g_shell.set);
	j = 1;
	if (!cmd[1])
	{
		i = 0;
		env_var = malloc((n + 1) * sizeof(char *));
		while (g_shell.set[i])
		{
			env_var[i] = g_shell.set[i];
			i++;
		}
		env_var[i] = NULL;
		i = 0;
		ft_sort_export(env_var);
		while (env_var[i])
		{
			ft_print_declare(env_var[i++]);
		}
		free(env_var);
		g_shell.status = 0;
		return (1);
	}
	while (cmd[j])
	{
		i = ft_var_is_present(cmd[j]);
		if (i >= 0)
		{
			ft_swap_var_val(i, cmd[j]);
		}
		else if (ft_input_is_valid(cmd[j]))
		{
			i = 0;
			n = ft_array_len(g_shell.set);
			env_var = malloc((n + 2) * sizeof(char *));
			while (g_shell.set[i])
			{
				env_var[i] = g_shell.set[i];
				i++;
			}
			env_var[i++] = ft_strdup(cmd[j]);
			env_var[i] = 0;
			free(g_shell.set);
			g_shell.set = env_var;
			g_shell.status = 0;
		}
		j++;
	}
	return (1);
}

int	ft_env(char **cmd)
{
	char	**env;
	int		i;

	i = 0;
	env = g_shell.set;
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
	return (1);
}
