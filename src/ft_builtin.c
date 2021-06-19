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

int		ft_env(char **cmd)
{
	char **env;
	int	i;
	
	i = 0;
	env = g_shell.set;
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
	return (1);
}

int		ft_export(char **cmd)
{
	int	n;
	int i;
	int j;
	char **env_var;

	i = 0;
	j = 0;
	n = ft_array_len(g_shell.set);
	//while (cmd[j++]);
	env_var = malloc(n+2);
	while(g_shell.set[i])
	{
		env_var[i] = g_shell.set[i];
		i++;
	}
	// while (cmd[j++])
	// {
	// 	env_var[i++] = ft_strdup(cmd[j++]);
	// }
	env_var[i++] = ft_strdup(cmd[1]);
	env_var[i] = 0;
	free(g_shell.set);
	g_shell.set = env_var;
	printf("%s\n", "Wanna export?");
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

int		ft_fn_selector(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(0,0));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(cmd));
	return (0);
}
