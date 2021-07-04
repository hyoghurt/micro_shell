#include "minishell.h"

void	ft_exp_args(char **cmd);
void	ft_swap_val(int i, char *s);
int		ft_var_is_present(char *s);

int	ft_export(char **cmd)
{
	g_shell.status = 0;
	if (cmd[1] == 0)
		ft_exp_no_args();
	else
		ft_exp_args(cmd);
	return (1);
}

void	ft_exp_args(char **cmd)
{
	int		i;
	int		j;

	j = 1;
	while (cmd[j])
	{
		if (ft_input_is_valid(cmd[j]))
		{
			i = ft_var_is_present(cmd[j]);
			if (i >= 0)
				ft_swap_val(i, cmd[j]);
			else
				ft_add_var(cmd[j]);
		}
		else
			g_shell.status = 1;
		j++;
	}
}

void	ft_swap_val(int i, char *s)
{
	char	*var;

	if (ft_strchr(s, '='))
	{
		free(g_shell.set[i]);
		var = ft_strdup(s);
		if (var == 0)
			ft_exit("minishell: swap_var: malloc: ", "error");
		g_shell.set[i] = var;
	}
}

void	ft_add_var(char *s)
{
	char	**env_var;
	int		n;
	int		i;

	i = 0;
	n = ft_array_len(g_shell.set);
	env_var = malloc((n + 2) * sizeof(char *));
	while (g_shell.set[i])
	{
		env_var[i] = g_shell.set[i];
		i++;
	}
	env_var[i] = ft_strdup(s);
	if (env_var[i] == 0)
	{
		ft_free_bi(env_var);
		ft_exit("minishell: export add_var: malloc: ", "error");
	}
	i++;
	env_var[i] = 0;
	free(g_shell.set);
	g_shell.set = env_var;
}

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
				return (i);
			j++;
			if (g_shell.set[i][j] == 0)
				return (i);
		}
		if (g_shell.set[i][j] == '=' && !s[j])
			return (i);
		i++;
	}
	return (-1);
}
