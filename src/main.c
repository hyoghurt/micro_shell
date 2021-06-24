#include "minishell.h"

void	ft_finish_executor(void);
int		ft_check_line(void);

int	main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_start();
		while (ft_check_line())
			ft_read();
		if (ft_lexer())
			ft_putstr_fd("minishell: syntax error\n", 2);
		else
		{
			while (*g_shell.line)
			{
				ft_parser();
				if (g_shell.cmd_table)
					ft_executor();
				while (*g_shell.line == ';'
					|| *g_shell.line == ' ' || *g_shell.line == '\t')
					g_shell.line++;
				ft_finish_executor();
			}
		}
	}
}

int	ft_check_line(void)
{
	char	*s;
	size_t	i;

	i = 0;
	s = g_shell.line;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (!s[i])
	{
		s[0] = '\0';
		return (1);
	}
	return (0);
}

void	ft_finish_executor(void)
{
	if (g_shell.cmd_table)
		ft_cmdclear(&g_shell.cmd_table);
}
