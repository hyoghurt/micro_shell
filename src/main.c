#include "minishell.h"

void	ft_finish_executor(void);
int		ft_check_line(void);

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_start();
		ft_read();
		if (!ft_check_line())
		{
			if (ft_lexer())
				ft_putstr_fd("minishell: syntax error\n", 2);
			else
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
		}
	}
}

int		ft_check_line(void)
{
	char	*s;
	size_t	i;

	if (shell.line)
	{
		i = 0;
		s = shell.line;
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
		{
			ft_story_del_front(&shell.story);
			return (1);
		}
		return (0);
	}
	return (1);
}

void	ft_finish_executor(void)
{
	ft_cmdclear(&shell.cmd_table);
	shell.fd_in = 0;
	shell.fd_out = 1;
	shell.fd_in_file = 0;
	shell.fd_out_file = 0;
}
