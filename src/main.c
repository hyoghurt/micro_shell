#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	signal(SIGINT, ft_sigfunc);
	ft_init_struct();
	ft_init_termios();
	while (1)
	{
		ft_set_prompt();
		shell.line = ft_read();
		//if (shell.line)
		//{
		printf("shell.line=\t[%s]\n", shell.line);
		printf("iterartion=\t[%d]\n", i);
		ft_parser();
		ft_executor(envp);
		i++;
		//}
	}
}
