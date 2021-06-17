#include "minishell.h"

void	ft_finish_executor(void);

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_start();
		ft_read();
		if (!ft_lexer())
		{
			while (*shell.line)
			{
				ft_parser();
				if (shell.cmd_table)
					ft_executor();
				if (*shell.line == ';')
					shell.line++;
				ft_finish_executor();
			}
		}
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

void	ft_finish_executor(void)
{
	ft_cmdclear(&shell.cmd_table);
	shell.fd_in = 0;
	shell.fd_out = 1;
	shell.fd_in_file = 0;
	shell.fd_out_file = 0;
}
