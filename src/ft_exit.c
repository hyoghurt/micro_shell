#include "minishell.h"

int	ft_print_error(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_free_bi(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_free_shell(void)
{
	if (g_shell.cmd_table)
		ft_cmdclear(&g_shell.cmd_table);
	if (g_shell.set)
		ft_free_bi(g_shell.set);
	if (g_shell.pathtkn)
		free(g_shell.pathtkn);
	if (g_shell.story)
		ft_story_clear(&g_shell.story);
}

int	ft_exit(char *msg, char *error)
{
	ft_free_shell();
	if (msg)
		ft_putstr_fd(msg, 2);
	if (error)
	{
		g_shell.status = ft_print_error();
		if (ft_strncmp(error, "err_tcgetattr", 13))
			exit (1);
	}
	tcsetattr(0, TCSANOW, &g_shell.termios_p);
	exit (g_shell.status);
}
