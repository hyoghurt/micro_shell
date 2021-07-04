#include "minishell.h"

char	**ft_sort_export(char **str);
void	ft_print_declare(char *s);

void	ft_exp_no_args(void)
{
	int		i;
	int		n;
	char	**env_var;

	i = -1;
	n = ft_array_len(g_shell.set);
	env_var = malloc((n + 1) * sizeof(char *));
	if (!env_var)
		ft_exit("minishell: export_no_arg: malloc: ", "error");
	while (g_shell.set[++i])
		env_var[i] = g_shell.set[i];
	env_var[i] = NULL;
	i = 0;
	ft_sort_export(env_var);
	while (env_var[i])
		ft_print_declare(env_var[i++]);
	free(env_var);
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

void	ft_print_declare(char *s)
{
	ft_putstr_fd("declare -x ", 1);
	while (*s && *s != '=')
		write(1, s++, 1);
	if (*s)
	{
		write(1, s, 1);
		write(1, "\"", 1);
		s++;
		while (*s)
			write(1, s++, 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}
