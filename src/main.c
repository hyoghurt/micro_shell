#include "minishell.h"

void	check_iter_and_line(int i)
{
	printf("\n\e[1;38;5;10mshell.line=\t[%s]\e[0m\n", shell.line);
}

void	ft_check_sintax_error(void)
{
	;
}

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_set_prompt();				//set prompt
		ft_read();						//read terminal
		ft_check_sintax_error();		//  !!!!!  write check ;;
		check_iter_and_line(0);			//debager_mzf
		write (1, "\n", 1);
		if (shell.line)					//if have command
		{
			while (*shell.line)			//loop if have ';'
			{
				ft_parser();			//parser command line
				ft_executor();			//processing command
				if (*shell.line == ';')
					shell.line++;
			}
		}
	}
}
