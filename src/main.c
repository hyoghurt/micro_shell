#include "minishell.h"

void	ft_start(void);
void	ft_finish_executor(void);

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);							//init terminal, init struct, save code key, copy envp in shell.set
	while (1)								//loop for new command string
	{
		ft_start();							//malloc(shell.line) , save shell.line in story
		ft_set_prompt();					//print prompt
		tputs(shell.key.sc, 1, ft_putint);	//save cursor position (need for backspace and move story)
		ft_read();							//read terminal	(create shell.line, check key, save shell.line in story)
		write (1, "\n", 1);

		while (*shell.line)					//loop if have ';'
		{
			ft_parser();					//parser shell.line (create shell.cmd_table)
			if (shell.cmd_table)
				ft_executor();				//PROCESING (use shell.cmd_table)
			if (*shell.line == ';')			//check ';' for loop
				shell.line++;
			ft_finish_executor();			//clear memory (clear(shell.cmd_table) free(shell.out_file) free(in_file)
		}
		//debag_check_story();
	}
}

void	ft_start(void)
{
	t_story	*new;

	shell.fg_mv_story = 0;						//flag for move story
	shell.line = ft_calloc(1, (BUF_SIZE * 2));
	//if (!shell.line)
	//ft_exit("minishell: init_read: malloc: ", "error");

	new = ft_story_new(shell.line);
	//if (!new)
	//write exit free story
	shell.move_story = new;						//save pointer story for move
	ft_story_add_front(&shell.story, new);
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



