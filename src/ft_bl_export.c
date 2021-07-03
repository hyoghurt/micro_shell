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
	ft_putstr_fd("declare -x ", 1);
	while (*s && *s != '=')
	{
		write(1, s, 1);
		s++;
	}
	if (*s)
	{
		write(1, s, 1);
		write(1, "\"", 1);
		s++;
		while (*s)
		{
			write(1, s, 1);
			s++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

int	ft_export(char **cmd)
{
	int		n;
	int		j;

	n = ft_array_len(g_shell.set);
	j = 1;
	ft_exp_noargs(cmd, n, j);
	ft_export_args(cmd, n, j);
	return (1);
}

char	**ft_sort_export(char **str)
{
	char	*sort;
	int		i;
	int		m;

	if (str == NULL)
		return (NULL);
	i = 0;
	m = 1;
	while (str[i] != NULL)
	{
		m = 1;
		while (str[i + m] != NULL)
		{
			if (ft_strncmp(str[i], str[i + m], ft_strlen(str[i])) > 0)
			{
				sort = str[i + m];
				str[i + m] = str[i];
				str[i] = sort;
			}
			m++;
		}
		i++;
	}
	return (str);
}
