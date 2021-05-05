#include "minishell.h"

void	check_iter_and_line(int i)
{
	printf("\n");
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
		ft_read();
		check_iter_and_line(i);	//debager_mzf
		write (1, "\n", 1);
		if (shell.line)
		{
			ft_parser();
			ft_executor();
		}
		i++;
	}
}
