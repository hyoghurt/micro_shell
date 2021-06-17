#include "minishell.h"


int		ft_echo(void)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!ft_strncmp(shell.cmd_table->token[1], "-n", 3))
	{
		i = 2;
		j = 1;
	}
	while (shell.cmd_table->token[i] != 0)
	{
		ft_putstr_fd(shell.cmd_table->token[i], 1);
		if (shell.cmd_table->token[i + 1] != 0)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (j == 0 )
		ft_putstr_fd("\n", 1);
	return (1);
}

int		ft_cd(void)
{
	char *path;
	int	ret;

	path = shell.cmd_table->token[1];
	ret = chdir(path);
	if (ret == -1)
		ft_print_string("minishell", path, strerror(errno));
	return (1);
}

int		ft_env(void)
{
	char **env;
	int	i;
	
	i = 0;
	env = shell.set;
	while (env[i])
	{
		printf("%s\n", env[i++]);
	}
	return (1);
}

int		ft_pwd(void)
{
	char *pwd;

	printf("We are in pwd!\n");

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int		ft_fn_selector(void)
{
	if (!ft_strncmp(shell.cmd_table->token[0], "echo", 5))
		return (ft_echo());
	if (!ft_strncmp(shell.cmd_table->token[0], "cd", 3))
		return (ft_cd());
	if (!ft_strncmp(shell.cmd_table->token[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(shell.cmd_table->token[0], "exit", 5))
		return (ft_exit(0,0));
	if (!ft_strncmp(shell.cmd_table->token[0], "env", 4))
		return (ft_env());
	return (0);
}
