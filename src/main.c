#include "minishell.h"

void	ft_start(void);
void	ft_finish_executor(void);

int		main(int argc, char **argv, char **envp)
{
	ft_init(envp);
	while (1)
	{
		ft_start();							//malloc(shell.line) , save shell.line in story
		ft_read();							//read terminal	(create shell.line, check key, save shell.line in story)
		if (!ft_lexer())
		{
			while (*shell.line)					//loop if have ';'
			{
				ft_parser();					//parser shell.line (create shell.cmd_table)
				if (shell.cmd_table)
					ft_executor();				//PROCESING (use shell.cmd_table)
				if (*shell.line == ';')			//check ';' for loop
					shell.line++;
				ft_finish_executor();			//clear memory (clear(shell.cmd_table) free(shell.out_file) free(in_file)
			}
		}
		else
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

void	ft_start(void)
{
	t_story	*new;

	ft_init_termios();
	shell.fg_mv_story = 0;						//flag for move story
	shell.line = ft_calloc(1, (BUF_SIZE * 2));
	if (!shell.line)
		ft_exit("minishell: init_read: malloc:", "error");
	new = ft_story_new(shell.line);
	if (!new)
	{
		free(shell.line);
		ft_exit("minishell: init_read: malloc:", "error");
	}
	shell.move_story = new;						//save pointer story for move
	ft_story_add_front(&shell.story, new);
	ft_set_prompt();
}

void	ft_finish_executor(void)
{
	ft_cmdclear(&shell.cmd_table);
}
