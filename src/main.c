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
			while (*shell.line)
			{
				ft_parser();
				if (shell.cmd_table)
					ft_executor();

				while (*shell.line == ';'
					|| *shell.line == ' ' || *shell.line == '\t')
					shell.line++;
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
	s = shell.line;
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
	if (shell.cmd_table)
		ft_cmdclear(&shell.cmd_table);
	shell.fd_in = 0;
	shell.fd_out = 1;
	shell.fd_in_file = 0;
	shell.fd_out_file = 0;
}
