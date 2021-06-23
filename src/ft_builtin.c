#include "minishell.h"

static void		echo_out(char **str, int pos)
{
	int		starts_with;
	int		ends_with;
	int		str_len;

	starts_with = IS_QUOTE(str[pos][0]);
	str_len = (int)ft_strlen(str[pos]);
	ends_with = IS_QUOTE(str[pos][str_len - 1]);
	if (ends_with && starts_with)
		ft_putnstr(str[pos] + 1, -1);
	else if (ends_with)
		ft_putnstr(str[pos], -1);
	else if (starts_with)
		ft_putstr_fd(str[pos + 1], 1);
	else
		ft_putstr_fd(str[pos],1);
	if (str[pos + 1])
		ft_putchar_fd(' ',1);
}

int		ft_echo(char **cmd)
{
	int		i;
	int		n_flag;

	//printf("%s\n", cmd[1]);
	n_flag = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
		n_flag = 1;
	i = 0;
	if (n_flag)
		++i;
	while (cmd[++i])
	{
		echo_out(cmd, i);
		if (!cmd[i + 1] && !n_flag)
			ft_putchar_fd('\n',1);
	}
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

	pwd = getcwd(NULL, 0);
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
