#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	signal(SIGINT, ft_sigfunc);
	ft_init_struct();
	ft_init_termios();
	while (1)
	{
		ft_set_prompt();
		shell.line = ft_read();
		//if (shell.line)
		//{
			ft_parser();
			ft_executor(envp);
			exit(0);
		//}
	}
}
