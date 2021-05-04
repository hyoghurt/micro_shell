#include "minishell.h"

void	check_iter_and_line(int i)
{
	printf("\e[1;38;5;10mshell.line=\t[%s]\e[0m\n", shell.line);
	printf("\e[1;38;5;10miterartion=\t[%d]\e[0m\n", i);
}

int		main(int argc, char **argv, char **envp)
{
	int	i = 0;

	ft_init(envp);
	while (1)
	{
		ft_set_prompt();
		shell.line = ft_read();
		//if (shell.line)
		//{
		check_iter_and_line(i);	//debager_mzf
		ft_parser();
		ft_executor();
		i++;
		//}
	}
}
