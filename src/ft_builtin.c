#include "minishell.h"

int		ft_echo(char **cmd)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (cmd[i] != 0)
	{
		if (i == 1)
		{
			if (!ft_strncmp(cmd[i], "-n", 3))
				j == 1;
		}
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] != 0)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (j == 0 )
		ft_putstr_fd("\n", 1);
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

	printf("We are in pwd!\n");

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
