#include "minishell.h"

int	ft_builting(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(cmd));
	else if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_bl_exit(cmd));
	return (0);
}
