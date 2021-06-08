#include "minishell.h"

int		ft_print_error(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_free_bi(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	*s = 0;
}

void	ft_cmdclear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*bg;

	tmp = *cmd;
	while (tmp)
	{
		bg = tmp;
		tmp = tmp->next;
		ft_free_bi(bg->token);
		free(bg);
	}
	*cmd = 0;
}

void	ft_free_shell(void)
{
	if (shell.line)
		free(shell.line);
	if (shell.cmd_table)
		ft_cmdclear(&shell.cmd_table);
	if (shell.out_file)
		free(shell.out_file);
	if (shell.in_file)
		free(shell.in_file);
	if (shell.set)
		ft_free_bi(shell.set);
	if (shell.pathtkn)
		free(shell.pathtkn);
}

int		ft_exit(char *msg, char *s)
{
	int	ret;

	ret = 0;
	ft_free_shell();
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s)
	{
		ret = ft_print_error();
		if (ft_strncmp(s, "err_tcgetattr", 13))
			exit (1);
	}
	if (tcsetattr(0, TCSANOW, &shell.termios_p) != 0)
		ret = ft_print_error();
	ft_putstr_fd("exit\n", 1);
	exit (ret);
}
