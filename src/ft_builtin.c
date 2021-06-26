#include "minishell.h"

static size_t	ft_check_n(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (1);
		}
		else
			return (i);
	}
	return (i);
}

int				ft_echo(char **args)
{
	size_t	i;
	int		n;

	n = 1;
	if (g_shell.status != 1)
		g_shell.status = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if ((!ft_strncmp(args[1], " ", ft_strlen(args[1]))) && !args[2])
		return (1);
	i = ft_check_n(args);
	n = i > 1 ? 0 : 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	return (1);
}

int		ft_cd(char **cmd)
{
	char *path;
	int	ret;

	path = cmd[1];
	ret = chdir(path);
	if (ret == -1)
		ft_print_string("minishell", path, strerror(errno));
	return (1);
}

int		ft_pwd(char **cmd)
{
	char *pwd;
	int i;
	int j;

	pwd = getcwd(NULL, 0);
	/// update $PWD and $OLDPWD
	// i = ft_var_is_present((char *) PWD);
	// j = ft_var_is_present((char *) OLDPWD);
	// ft_swap_var_val(j, oldpwd);
	// ft_swap_var_val(i, pwd);
	///
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int		ft_var_is_present(char *s)
{
	int i;
	int j;

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
	char *var;

	free(g_shell.set[i]);
	var = ft_strdup(s);
	if (var == 0)
		ft_exit(0,0);
	g_shell.set[i] = var;
}

void ft_print_declare(char *s)
{
	int i;

	i=0;
	ft_putstr_fd("declare -x ",1);
	while ( s[i] != '=')
	{
		write(1, &s[i],1);
		i++;
	}
	write(1, &s[i],1);
	write(1, "\"", 1);
	i++;
	while (s[i])
	{
		write(1, &s[i],1);
		i++;
	}
	write(1, "\"\n", 2);
}

int		ft_export(char **cmd)
{
	int	n;
	int i;
	int j;
	char **env_var;

	n = ft_array_len(g_shell.set);
	//env_var = malloc(n+2);
	j = 1;
	if (!cmd[1])
	{
		i = 0;
		env_var = malloc((n+1) * sizeof(char *));
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
		//printf("<--in no arg for export-->\n");
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
			env_var = malloc((n+2) * sizeof(char *));
			while(g_shell.set[i])
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
	// else{
	// 	printf("Input was invalid\n");
	// }
	// printf("%s\n", "-->in export-->\n");
	return (1);
}

int		ft_env(char **cmd)
{
	char **env;
	int	i;
	
	i = 0;
	env = g_shell.set;
	//printf("<--In env-->");
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
	return (1);
}

int		ft_fn_selector(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(cmd));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(0,0));
	return (0);
}
