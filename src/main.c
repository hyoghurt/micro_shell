#include "minishell.h"

//brew install readline

void	ft_finish_executor(void);

int		main(int argc, char **argv, char **envp)
{
	char *s;
	t_list	*new;

	ft_init(envp);
	while (1)
	{
		s = readline("\033[1;48;5;58mUSER > \033[0m");
		if (s && *s)
			add_history(s);
		new = ft_lstnew(s);
		ft_lstadd_back(&shell.story, new);
		shell.line = s;
		if (!ft_lexer())
		{
			ft_parser();					//parser shell.line (create shell.cmd_table)
			ft_executor();				//PROCESING (use shell.cmd_table)
			ft_finish_executor();			//clear memory (clear(shell.cmd_tabable
		}
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

void	ft_finish_executor(void)
{
	ft_cmdclear(&shell.cmd_table);
}
