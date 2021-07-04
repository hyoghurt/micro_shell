#include "minishell.h"

int		check_digit(char *s);
void	no_digit(char *s);
void	is_digit(char *s);

int	ft_bl_exit(char **cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd[1])
	{
		if (!check_digit(cmd[1]))
			no_digit(cmd[1]);
		else if (cmd[2])
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		else
			is_digit(cmd[1]);
	}
	else
		ft_exit(0, 0);
	return (1);
}

int	check_digit(char *s)
{
	while (*s)
	{
		if (ft_isdigit(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}

void	no_digit(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_print_string("exit", s, "___write__!!!");
	g_shell.status = 2;
	ft_exit(0, 0);
}

void	is_digit(char *s)
{
	g_shell.status = ft_atoi(s);
	if (g_shell.status >= 0)
		g_shell.status %= 256;
	while (g_shell.status < 0)
		g_shell.status += 256;
	ft_exit(0, 0);
}
