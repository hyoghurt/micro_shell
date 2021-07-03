#include "minishell.h"

int	ft_exp_noargs(char **cmd, int n, int j)
{
	int		i;
	char	**env_var;

	if (!cmd[j])
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
	return (0);
}

void	ft_export_args_help(char **cmd, int n, int i, int j)
{
	char	**env_var;

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
}

void	ft_export_args(char **cmd, int n, int j)
{
	int		i;

	while (cmd[j])
	{
		i = ft_var_is_present(cmd[j]);
		ft_export_args_help(cmd, n, i, j);
		j++;
	}
}
