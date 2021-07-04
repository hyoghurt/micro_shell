#include "minishell.h"

void	ft_cd_one(void);
void	ft_update_oldpwd(void);
void	ft_update_pwd(void);

int	ft_cd(char **cmd)
{
	if (cmd[1] == 0)
		ft_cd_one();
	else if (cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_shell.status = 1;
	}
	else if (chdir(cmd[1]) == -1)
	{
		ft_print_string("minishell", cmd[1], strerror(errno));
		g_shell.status = 1;
	}
	else
	{
		ft_update_oldpwd();
		ft_update_pwd();
		g_shell.status = 0;
	}
	return (1);
}

void	ft_cd_one(void)
{
	char	*path;

	path = ft_getset("HOME");
	if (*path == 0)
	{
		free(path);
		ft_putstr_fd("minishell: cd: no env HOME\n", 2);
		g_shell.status = 1;
	}
	else if (chdir(path) == -1)
	{
		ft_print_string("minishell", path, strerror(errno));
		free(path);
		g_shell.status = 1;
	}
	else
	{
		free(path);
		ft_update_oldpwd();
		ft_update_pwd();
		g_shell.status = 0;
	}
}

void	ft_update_oldpwd(void)
{
	char	*pwd;
	char	*full_oldpwd;
	int		i;

	i = ft_var_is_present("OLDPWD=");
	pwd = ft_getset("PWD");
	if (!pwd)
		ft_exit("minishell: update_oldpwd: malloc: ", "error");
	full_oldpwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!full_oldpwd)
		ft_exit("minishell: update_oldpwd: malloc: ", "error");
	if (i >= 0)
		ft_swap_var_val(i, full_oldpwd);
	//else
	//write export full_oldpwd
}

void	ft_update_pwd(void)
{
	char	*pwd;
	char	*full_pwd;
	int		i;

	i = ft_var_is_present("PWD=");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit("minishell: update_oldpwd: malloc: ", "error");
	full_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!full_pwd)
		ft_exit("minishell: update_pwd: malloc: ", "error");
	if (i >= 0)
		ft_swap_var_val(i, full_pwd);
	//else
	//write export full_pwd
}
