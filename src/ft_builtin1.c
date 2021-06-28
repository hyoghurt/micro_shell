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

int	ft_echo(char **args)
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
	//n = i > 1 ? 0 : 1;
	if ((n = 1) > 1)
	 	return 0;
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

void	ft_update_oldpwd(void)
{
	char	*string;
	char	*full_oldpwd;
	int		i;

	i = ft_var_is_present("OLDPWD=");
	string = ft_getset("PWD");
	full_oldpwd = ft_strjoin("OLDPWD=", string);
	ft_swap_var_val(i, full_oldpwd);
}

void	ft_update_pwd(void)
{
	char	*pwd;
	char	*full_pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	i = ft_var_is_present("PWD=");
	full_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	ft_swap_var_val(i, full_pwd);
}

int	ft_cd(char **cmd)
{
	char	*path;
	int		ret;

	g_shell.status = 0;
	if (cmd && cmd[1] && cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_shell.status = 1;
		return (1);
	}
	path = cmd[1];
	ret = chdir(path);
	if (ret == -1)
	{
		ft_print_string("minishell", path, strerror(errno));
		g_shell.status = 1;
		return (1);
	}
	ft_update_oldpwd();
	ft_update_pwd();
	return (1);
}
