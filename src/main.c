#include "minishell.h"

void	ft_start(void)
{
	t_story	*new;

	shell.fg_mv_story = 0;
	shell.line = ft_calloc(1, (BUF_SIZE * 2));
	//if (!shell.line)
	//ft_exit("minishell: init_read: malloc: ", "error");

	new = ft_story_new(shell.line);
	//if (!new)
	//write exit free story
	shell.move_story = new;
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
}

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_start();
		ft_set_prompt();				//set prompt
		tputs(shell.key.sc, 1, ft_putint);
		ft_read();						//read terminal	(create shell.line)
		write (1, "\n", 1);
		while (*shell.line)				//loop if have ';'
		{
			ft_parser();				//parser command line
			if (shell.cmd_table)
				ft_executor();				//processing command
			if (*shell.line == ';')
				shell.line++;
			ft_finish_executor();
		}
		//debag_check_story();
	}
}
