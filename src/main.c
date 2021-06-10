#include "minishell.h"

void	ft_finish_executor(void);

int		main(int argc, char **argv, char **envp)
{
	char *s;

	ft_init(envp);							//init terminal, init struct, save code key, copy envp in shell.set
	while (1)								//loop for new command string
	{
		s = readline("\033[1;48;5;58mUSER > \033[0m");
		if (s && *s)
			add_history(s);
		shell.line = ft_strdup(s);
		if (!ft_lexer())
		{
			ft_parser();					//parser shell.line (create shell.cmd_table)
			//if (shell.cmd_table)
			ft_executor();				//PROCESING (use shell.cmd_table)
			ft_finish_executor();			//clear memory (clear(shell.cmd_table) free(shell.out_file) free(in_file)
		}
	}
}

void	ft_finish_executor(void)
{
	ft_cmdclear(&shell.cmd_table);
	if (shell.in_file)
		free(shell.in_file);
	if (shell.out_file)
		free(shell.out_file);
	shell.in_file = 0;
	shell.out_file = 0;
	shell.std.fd_in = 0;
	shell.std.fd_out = 1;
}
